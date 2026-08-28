# Arquitetura de Firmware: `ao_watch`

Este documento consolida as decisões arquiteturais do smartwatch `ao_watch`. A arquitetura foi desenhada para garantir máxima performance (usando QP/C e DMA), baixo acoplamento e altíssima facilidade de manutenção.

---

## 1. As Quatro Camadas (O Mapa Mental)
A regra de ouro deste projeto é separar **"o que está dentro do chip"** do **"que está fora do chip"**.

1. **`Core/` (A Fiação Interna):** Cuida exclusivamente do silício do STM32. Liga os clocks, configura os pinos (GPIO) e inicializa os periféricos (SPI, I2C). O *Core* não sabe o que é um Display ou um Acelerômetro.
2. **`lib/BSP/` (Os Eletrodomésticos):** O *Board Support Package*. É o código que sabe ligar os pinos do STM32 aos chips físicos da placa. Ele esconde toda a sujeira elétrica e do HAL da ST, oferecendo botões fáceis para a Aplicação usar (ex: `BSP_Display_Flush()`).
3. **`lib/components/` (A Matemática Pura):** Bibliotecas genéricas de código aberto (ex: `adxl362`, `ls013b7dh03`). Essas bibliotecas não sabem que o STM32 existe. Elas são 100% C puro e portáveis.
4. **`app/` (O Cérebro / QP/C):** A Máquina de Estados. Contém as regras de negócio. Decide *quando* ler um sensor e *quando* mudar a tela. Nunca toca no hardware diretamente.

---

## 2. A Estrutura de Pastas

```text
ao_watch/
├── core/
│   ├── inc/
│   │   ├── spi.h         # Declara: extern SPI_HandleTypeDef hspi1; e hspi2;
│   │   └── ...
│   └── src/
│       ├── main.c        # HAL_Init(), SystemClock_Config(), spi_init(), QF_run()
│       ├── spi.c         # Apenas liga a energia do SPI. Sem lógica de leitura/escrita.
│       └── gpio.c
│
├── lib/
│   ├── BSP/
│   │   ├── inc/
│   │   │   ├── bsp_display.h
│   │   │   └── bsp_accel.h
│   │   └── src/
│   │       ├── bsp_display.c  # Absorve a interface da lib genérica do LS013B7.
│   │       └── bsp_accel.c    # Absorve a interface da lib genérica do ADXL362.
│   │
│   ├── components/
│   │   ├── adxl362/           # Lib genérica. (Arquivos *_interface.c foram DELETADOS!)
│   │   ├── ls013b7dh03/       # Lib genérica. (Arquivos *_interface.c foram DELETADOS!)
│   │   └── algorithms/        # Filtros matemáticos DSP (cálculo de passos, HR).
│   │
│   └── third_party/
│       └── stm32cubewb/       # A HAL intocada da STMicroelectronics.
│
└── app/
    ├── watch.c                # AO_Watch: Máquina de estados das telas (LVGL).
    └── sensores.c             # AO_Sensores: Máquina de estados que coleta os dados.
```

---

## 3. Decisões Arquiteturais Chave

### 3.1. Dois Barramentos SPI (Performance e Anti-Colisão)
Optamos por abandonar o barramento compartilhado.
*   **SPI1:** Dedicado ao Display (LS013B7DH03). Permite enviar a imagem inteira usando DMA (fundo de tela) sem travar a CPU. Pede Chip Select (CS) em nível **HIGH**.
*   **SPI2:** Dedicado ao Acelerômetro (ADXL362). Pede Chip Select (CS) em nível **LOW**.
*   *Benefício:* Zero necessidade de Semáforos (`spi_lock` do FreeRTOS foram deletados).

### 3.2. O Padrão "Thick BSP" (A Fusão da Interface)
Bibliotecas genéricas exigem que o usuário implemente uma `interface.c` com funções de hardware. Em vez de criarmos arquivos confusos, **o próprio arquivo BSP absorve essas funções**.

**Como funciona (Exemplo do Display):**
O arquivo `lib/BSP/src/bsp_display.c` inclui a HAL da ST e define as funções que a biblioteca genérica espera:
```c
// Dentro de bsp_display.c
uint8_t ls013b7dh03_interface_spi_write(uint8_t *buf, uint16_t len) {
    // Usa a hspi1 que veio do core/inc/spi.h via extern
    if (HAL_SPI_Transmit(&hspi1, buf, len, 500) == HAL_OK) return 0;
    return 1;
}

void ls013b7dh03_interface_cs_control(uint8_t state) {
    if (state == 1) HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_SET);
    else HAL_GPIO_WritePin(DISP_CS_PORT, DISP_CS_PIN, GPIO_PIN_RESET);
}
```

### 3.3. Pipeline de Tratamento de Dados (A Filosofia Active Object)
Para não travar a fluidez da interface gráfica (LVGL), o tratamento de dados matemáticos é separado da UI usando o QP/C:

1. **Gatilho:** O `AO_Sensores` acorda a cada 20ms (Time Event).
2. **Coleta (BSP):** O `AO_Sensores` pede um array de dados crus para o hardware (`BSP_MAX30102_ReadFIFO(raw_array, 32)`).
3. **Processamento (Algorithms):** O `AO_Sensores` joga o array elétrico cru em uma função puramente matemática da pasta `lib/algorithms` (Beningo style). O algoritmo processa e encontra `85 BPM`.
4. **Transporte (QP/C):** O `AO_Sensores` empacota esse "85" numa carta (Evento) e envia para a fila do `AO_Watch`.
5. **Tela (UI):** O `AO_Watch` recebe a carta e apenas manda a biblioteca gráfica atualizar o texto na tela.

Essa arquitetura garante que o microcontrolador possa calcular derivadas e filtros complexos em background sem perder um único frame da animação do relógio.
