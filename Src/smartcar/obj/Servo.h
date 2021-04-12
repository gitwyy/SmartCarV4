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
     * ��ȡ�����ת��Ƕ�
     * @return
     */
    float getRadian();

    /**
     * ���ƶ��ת��,��λΪ����
     * @param rad
     */
    void setRadian(double rad);

    void setPwm(int pwm);
};

#endif
#endif //SMARTCARV4_SERVO_H
