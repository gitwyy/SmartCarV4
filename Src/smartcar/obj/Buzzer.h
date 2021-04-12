//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_BUZZER_H
#define SMARTCARV4_BUZZER_H

#include "stm32f1xx_hal.h"

#ifdef __cplusplus

class Buzzer {

public:
    Buzzer(GPIO_TypeDef *port, uint16_t pin);

    ~Buzzer();

private:
    GPIO_TypeDef *port;
    uint16_t pin;

public:
    void open();

    void toggle();

    void close();

    bool isOpen();

};

#endif
#endif //SMARTCARV4_BUZZER_H
