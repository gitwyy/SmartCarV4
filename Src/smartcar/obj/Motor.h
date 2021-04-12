//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_MOTOR_H
#define SMARTCARV4_MOTOR_H

#include "stm32f1xx_hal.h"

class Motor {
public:
    /**
     * ���
     * @param portA ��������ת
     * @param pinA ��������ת
     * @param portB ��������ת
     * @param pinB ��������ת
     * @param tim   ����PWM�ģ�����������ʣ�
     * @param channel   ��ʱ��ͨ��
     * @param direction  ����������������ת������
     */
    Motor(GPIO_TypeDef *portA, uint16_t pinA, GPIO_TypeDef *portB, uint16_t pinB, TIM_HandleTypeDef *tim,
          uint16_t channel, int direction);

    GPIO_TypeDef *portA;
    uint16_t pinA;

    GPIO_TypeDef *portB;
    uint16_t pinB;

    TIM_HandleTypeDef *tim;
    uint16_t channel;

    int lastPwm;

    /** ���ת��ϵ�� */
    int direction;

    /** ���ת�� */
    void spin(int pwm);

    /** ����ʼ�� */
    void init();

    virtual ~Motor();
};


#endif //SMARTCARV4_MOTOR_H
