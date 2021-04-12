//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_ENCODER_H
#define SMARTCARV4_ENCODER_H

#include "stm32f1xx_hal.h"

class Encoder {
public:
    Encoder(TIM_HandleTypeDef *tim, uint16_t channel, int direction);

    ~Encoder();

    TIM_HandleTypeDef *tim;
    uint16_t channel;
    int direction;

    void init();

    short read();
};

#endif //SMARTCARV4_ENCODER_H