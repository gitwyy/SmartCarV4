//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_MOTOR_H
#define SMARTCARV4_MOTOR_H

#include "stm32f1xx_hal.h"

class Motor {
public:
    /**
     * 电机
     * @param portA 控制正反转
     * @param pinA 控制正反转
     * @param portB 控制正反转
     * @param pinB 控制正反转
     * @param tim   控制PWM的（控制输出功率）
     * @param channel   定时器通道
     * @param direction  后续方便调整电机的转动方向
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

    /** 马达转向系数 */
    int direction;

    /** 马达转动 */
    void spin(int pwm);

    /** 马达初始化 */
    void init();

    virtual ~Motor();
};


#endif //SMARTCARV4_MOTOR_H
