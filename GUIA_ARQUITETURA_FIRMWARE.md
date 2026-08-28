# Arquitetura de Firmware Profissional (Estilo Peng Zhihui)

Analisando os repositórios **Dummy-Robot** e **ElectronBot** do *Peng Zhihui* (Zhihui Jun), podemos extrair uma masterclass de como organizar projetos de sistemas embarcados e robótica em C/C++. 

Ele utiliza uma abordagem rigorosamente separada em **camadas** e aproveita o paradigma de Orientação a Objetos do **C++** para manter o código limpo, modular e fácil de escalar.

Abaixo, detalho como ele faz isso e como você pode aplicar exatamente os mesmos conceitos no seu projeto `ao_watch`.

---

## 1. A Pirâmide de Camadas (A Arquitetura)

Nos projetos do Peng Zhihui, a pasta raiz do firmware sempre é dividida nas seguintes pastas chave:

```text
📁 Firmware/
├── 📁 Core/        (e 📁 Drivers/) -> Camada de Hardware (Gerada)
├── 📁 Bsp/         -> Camada de Drivers de Placa (Board Support Package)
├── 📁 Robot/       -> Camada de Domínio / Middleware (Lógica independente)
└── 📁 UserApp/     -> Camada de Aplicação (Onde fica o main.cpp e as Threads)
```

### 🔹 1. Camada de Hardware (`Core/` e `Drivers/`)
**O que é:** Aqui ficam os códigos gerados automaticamente pelas ferramentas da fabricante (como o *STM32CubeMX*) e as bibliotecas HAL (Hardware Abstraction Layer).
**Regra de Ouro:** Você **nunca** escreve sua lógica de aplicação aqui. Se precisar configurar um pino novo, você gera pela ferramenta visual do microcontrolador e ela atualiza essa pasta.

### 🔹 2. Camada BSP (`Bsp/` - Board Support Package)
**O que é:** É aqui que você cria os "Drivers" para os componentes físicos da sua placa. 
**Como o Peng faz:** Ele não chama funções sujas da HAL direto na aplicação. Em vez disso, ele cria arquivos como `Bsp/imu/MPU6050.cpp` ou `Bsp/screen.cpp`. 
Esses arquivos traduzem coisas complexas como "Enviar byte `0x32` pelo pino I2C usando `HAL_I2C_Mem_Read`" para funções amigáveis como `imu.getAcceleration()`.
**O que você deve colocar aqui no `ao_watch`:**
- `display_st7789.c` (ou `.cpp`)
- `sensor_batimento.c`
- `botoes.c`

### 🔹 3. Camada de Middleware / Domínio (`Robot/` ou `Middlewares/`)
**O que é:** Lógica pura. Códigos que não fazem ideia de qual microcontrolador você está usando. Se você trocar de um STM32 para um ESP32, essa pasta continua idêntica.
**Como o Peng faz:** Ele cria pastas como `Robot/algorithms` para calcular a cinemática do robô, ou filtros matemáticos. Ele também coloca sistemas operacionais (FreeRTOS) e pilhas USB aqui.
**No `ao_watch`:**
- Sistema de Menus (UI) independentes de tela.
- Contadores de passos (Algoritmo matemático puro).
- Gerenciamento de Arquivos/Memória (FatFS, LittleFS).

### 🔹 4. Camada de Aplicação (`UserApp/`)
**O que é:** O cérebro que liga todas as partes debaixo.
**Como o Peng faz:** O arquivo `main.c` gerado pela IDE serve apenas para inicializar o hardware e chamar a função `Main()` (com M maiúsculo) que fica isolada no arquivo `UserApp/main.cpp`.
Ele usa **FreeRTOS** ativamente, então o `main.cpp` basicamente inicializa as Threads (Tarefas):
- `ThreadControlLoop`: Lê sensores e comanda motores em tempo real (Prioridade Alta).
- `ThreadOledUpdate`: Atualiza a tela a cada X milissegundos (Prioridade Baixa).

---

## 2. O Segredo do C++ no Embarcado

O maior pulo do gato para parar de se sentir confuso é abandonar o padrão de C puro usando variáveis globais soltas, e adotar C++. O Peng Zhihui cria **Classes** para representar o hardware.

Exemplo real do `main.cpp` do Dummy-Robot:

```cpp
// UserApp/main.cpp

// Ele instancia os hardwares globais amarrando eles à porta do microcontrolador!
SSD1306 oled(&hi2c0);      // Tela OLED ligada no I2C_0
MPU6050 mpu6050(&hi2c1);   // Sensor de inclinação no I2C_1
DummyRobot dummy(&hcan1);  // Motores ligados via rede CAN_1

void ThreadOledUpdate(void* argument) {
    for (;;) {
        // A lógica fica MUITO limpa. Ele não precisa saber qual pino é o do OLED aqui!
        oled.clearBuffer();
        oled.printf("IMU:%.3f/%.3f", mpu6050.data.ax, mpu6050.data.ay);
        oled.sendBuffer();
        
        osDelay(20); // Espera 20ms e libera o processador
    }
}
```
Viu como ele não se preocupa com `HAL_I2C_Master_Transmit` na camada de aplicação? A classe `SSD1306` dentro do BSP abstraiu tudo isso de forma elegante.

---

## 3. Como estruturar o seu `ao_watch` AGORA

Atualmente seu projeto `ao_watch` tem tudo centralizado ou numa estrutura flat. Para seguir um padrão profissional, recomendo a seguinte reestruturação de pastas:

1. **Ative o suporte a C++ (se já não estiver):** Facilite a criação de componentes orientados a objetos.
2. **Crie a árvore de pastas correta. Veja como deve ficar seu repositório:**

```text
ao_watch/
├── cmake/              # Seus scripts de build
├── core/               # (Deixe aqui apenas o que é gerado pela fabricante/CMSIS/HAL)
│   ├── inc/
│   └── src/            # main.c (gerado), stm32f4xx_it.c, etc.
├── bsp/                # SEUS DRIVERS DE PLACA (BOARD SUPPORT PACKAGE)
│   ├── display/
│   │   ├── display.hpp
│   │   └── display.cpp # Código que fala com o SPI para desenhar na tela
│   ├── power/          # Bateria, botão de ligar/sleep
│   └── sensors/        # Acelerômetro, batimento cardíaco, GPS
├── middleware/         # BIBLIOTECAS INDEPENDENTES
│   ├── lvgl/           # Biblioteca para desenhar botões e interfaces
│   └── FreeRTOS/       # Sistema operacional em tempo real
└── app/                # SUA APLICAÇÃO (A ALMA DO PROJETO)
    ├── watchfaces/     # Lógicas puras de cada interface do relógio
    ├── threads/        # Arquivos separando as tarefas simultâneas
    │   ├── ui_thread.cpp
    │   └── sensor_thread.cpp
    └── app_main.cpp    # Ponto de entrada real do relógio
```

### O Fluxo de Comunicação Inteligente:
* **Regra de Ouro:** A sua Tela nunca deve tentar ler o Sensor de Batimentos diretamente. 
* A `sensor_thread.cpp` (na pasta App) faz a leitura chamando o driver no `bsp/sensors/`.
* A `sensor_thread.cpp` salva esse dado de forma segura.
* A `ui_thread.cpp` (App) lê esse valor salvo e manda desenhar chamando o driver `bsp/display/` (ou LVGL).

Dessa forma, se no meio do projeto você trocar a fabricante da tela ou o modelo do sensor, você **só altera a pasta BSP**. O resto do `ao_watch` inteiro continua funcionando 100% igual e sem causar bugs!

---

## 4. O Padrão Wrapper: Simplificando Bibliotecas Genéricas

Para acabar com a proliferação de arquivos (interface.c, basic_application.c, etc.) mantendo as bibliotecas genéricas intactas, usamos a camada **BSP (Board Support Package)** como uma "Capa" (Wrapper). 

Abaixo está o teste de mesa e o código de como isso funciona na prática para um acelerômetro (ADXL362).

### 4.1. O Arquivo Header (Visão da Aplicação)
O arquivo .h do BSP é a única coisa que a sua máquina de estados vai enxergar. Note que ele **não** inclui a biblioteca do sensor. Ele é totalmente burro e genérico.

**Arquivo: bsp/bsp_accelerometer.h**
`c
#ifndef BSP_ACCELEROMETER_H
#define BSP_ACCELEROMETER_H

#include <stdint.h>

// A máquina de estados só precisa conhecer estas 3 funções:
void BSP_Accel_Init(void);
uint32_t BSP_Accel_GetSteps(void);
void BSP_Accel_Sleep(void);

#endif // BSP_ACCELEROMETER_H
`

### 4.2. O Arquivo Source (A Mágica da Cola)
Aqui dentro nós juntamos o STM32 (HAL), a sua biblioteca genérica (adxl362.h) e fazemos o casamento. 

**Arquivo: bsp/bsp_accelerometer.c**
`c
#include "bsp_accelerometer.h"
#include "adxl362.h"        // Sua biblioteca genérica (libdrive)
#include "stm32wbxx_hal.h"  // O hardware real

extern SPI_HandleTypeDef hspi1; // O SPI do seu STM32

// 1. AS FUNÇÕES "FEIAS" DE HARDWARE (Escondidas com 'static')
static void SPI_WriteBytes(uint8_t reg, uint8_t *data, uint16_t len) {
    // Código real do STM32 manipulando o pino CS e enviando dados
    HAL_GPIO_WritePin(GPIOA, CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);
    HAL_SPI_Transmit(&hspi1, data, len, 100);
    HAL_GPIO_WritePin(GPIOA, CS_PIN, GPIO_PIN_SET);
}

static void SPI_ReadBytes(uint8_t reg, uint8_t *data, uint16_t len) {
    // Código real de leitura do STM32...
}

// 2. A FUNÇÃO DE INICIALIZAÇÃO DA FACHADA
void BSP_Accel_Init(void) {
    // Passamos as funções do STM32 para a biblioteca genérica
    adxl362_init_t init_config;
    init_config.spi_write = SPI_WriteBytes; 
    init_config.spi_read = SPI_ReadBytes;
    
    // Inicializamos a biblioteca genérica
    adxl362_init(&init_config);
    adxl362_start_step_counter();
}

// 3. A FUNÇÃO DE LEITURA DA FACHADA
uint32_t BSP_Accel_GetSteps(void) {
    uint32_t steps = 0;
    // Pede para a biblioteca ler. A biblioteca vai chamar o SPI_ReadBytes internamente.
    adxl362_read_steps(&steps);
    return steps;
}
`

### 4.3. A Integração na sua HSM (O Teste de Mesa)
Agora vamos ver como a sua máquina de estados no **QM Tool** vai usar isso. O seu código de aplicação fica extremamente limpo e livre de HAL.

**No código de Ação (Action) do seu QM Tool:**
`c
#include "qpc.h"
#include "bsp.h"                 // Onde o BSP_Accel_Init e etc devem estar agrupados
#include "bsp_accelerometer.h"   // Trazemos a visão limpa do sensor

// ... Código da HSM gerado ...

static QState Watch_timekeeping(Watch * const me, QEvt const * const e) {
    switch (e->sig) {
        
        case Q_ENTRY_SIG: {
            BSP_Accel_Init(); // Liga o acelerômetro ao entrar no modo relógio
            return Q_HANDLED();
        }
        
        case TICK_SIG: { 
            // A cada 1 segundo (Tick do QP/C), lemos os passos
            uint32_t steps = BSP_Accel_GetSteps();
            
            // Mandamos para a tela (LVGL)
            Ui_UpdateSteps(steps);
            
            return Q_HANDLED();
        }
        
        case Q_EXIT_SIG: {
            BSP_Accel_Sleep(); // Põe pra dormir se sair do modo relógio
            return Q_HANDLED();
        }
        // ...
    }
}
`

### O "Andar do Código" (Fluxo de Execução - Teste de Mesa)
Quando o sistema estiver rodando, este é o caminho que a informação faz:

1. **A Aplicação Pede (HSM):** O Tick do QP/C avisa a máquina de estados que passou 1 segundo. A HSM executa BSP_Accel_GetSteps().
2. **O BSP Intermedia:** A função BSP_Accel_GetSteps() recebe o pedido e manda a biblioteca genérica agir executando dxl362_read_steps(&steps).
3. **A Lib Genérica Trabalha:** O arquivo adxl362.c (que é agnóstico) descobre qual registrador precisa ler e chama o seu ponteiro de função interno (spi_read).
4. **O Hardware Atua:** O ponteiro cai na função SPI_ReadBytes dentro do BSP, que finalmente executa o HAL_SPI_Transmit manipulando os bits elétricos no pino do STM32.
5. **O Retorno:** O dado elétrico volta pela mesma cadeia até chegar na HSM, que envia o valor finalizado para o display LVGL.

