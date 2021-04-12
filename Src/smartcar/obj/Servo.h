//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_SERVO_H
#define SMARTCARV4_SERVO_H

#include "stm32f1xx_hal.h"
#include "../config/config.h"

#ifdef __cplusplus

class Servo {
public:
    Servo(TIM_HandleTypeDef *tim, uint32_t channel);

    ~Servo();

private:
    TIM_HandleTypeDef *tim;
    uint32_t channel;
    float radian = 0;
public:

    void init();

    /**
     * 获取舵机的转向角度
     * @return
     */
    float getRadian();

    /**
     * 控制舵机转向,单位为弧度
     * @param rad
     */
    void setRadian(double rad);

    void setPwm(int pwm);
};

#endif
#endif //SMARTCARV4_SERVO_H
