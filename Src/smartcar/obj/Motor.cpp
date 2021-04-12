//
// Created by wangyangyang on 2021-04-10.
//

#include "Motor.h"
#include "../config/config.h"
#include "math.h"

Motor::Motor(GPIO_TypeDef *portA, uint16_t pinA, GPIO_TypeDef *portB, uint16_t pinB, TIM_HandleTypeDef *tim,
             uint16_t channel, int direction) {
    this->portA = portA;
    this->pinA = pinA;
    this->portB = portB;
    this->pinB = pinB;
    this->tim = tim;
    this->channel = channel;
    this->direction = direction;
}

void Motor::init() {
    HAL_GPIO_WritePin(this->portA, this->pinA, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(this->portB, this->pinB, GPIO_PIN_RESET);

    HAL_TIM_PWM_Start(this->tim, this->channel);
    __HAL_TIM_SET_COMPARE(this->tim, this->channel, 0);
}

void Motor::spin(int pwm) {
    // pwm���Ʒ�Χ
    if (pwm > MAX_PWM) {
        pwm = MAX_PWM;
    } else if (pwm < MIN_PWM) {
        pwm = MIN_PWM;
    }


    pwm *= this->direction;

    // ��������,������ε�pwm ����һ�ε�pwm����һ��
    if (pwm * lastPwm < 0) {
        HAL_GPIO_WritePin(this->portA, this->pinA, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->portB, this->pinB, GPIO_PIN_RESET);
    }

    lastPwm = pwm;
    if (pwm > 0) { // ��ת
        HAL_GPIO_WritePin(this->portB, this->pinB, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->portA, this->pinA, GPIO_PIN_SET);
    } else if (pwm < 0) {
        HAL_GPIO_WritePin(this->portA, this->pinA, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->portB, this->pinB, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(this->portA, this->pinA, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->portB, this->pinB, GPIO_PIN_RESET);
    }

    __HAL_TIM_SET_COMPARE(this->tim, this->channel, abs(pwm));
}

Motor::~Motor() {

}
