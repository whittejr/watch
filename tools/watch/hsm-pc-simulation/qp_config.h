#ifndef QP_CONFIG_H
    #define QP_CONFIG_H

    // Define o número máximo de Active Objects rodando ao mesmo tempo (ajuste depois se precisar)
    #define QF_MAX_ACTIVE      8

    // Define o tamanho máximo dos pools de memória (usado se você criar eventos com dados)
    #define QF_MAX_EPOOL       2

    // Tamanho em bytes dos contadores internos (1, 2 ou 4). Mantemos pequeno para economizar RAM.
    #define QF_TIMEEVT_CTR_SIZE 2
    #define QF_EVENT_SIZ_SIZE   2

    #endif /* QP_CONFIG_H */