//
// Created by wangyangyang on 2021-04-10.
//

#include "Servo.h"
#include "../util/RobotLog.h"
#include <math.h>


Servo::Servo(TIM_HandleTypeDef *tim, uint32_t channel) {
    this->tim = tim;
    this->channel = channel;
}

Servo::~Servo() {}

void Servo::init() {
    HAL_TIM_PWM_Start(this->tim, this->channel);
    setRadian(0);
}

void Servo::setRadian(double rad) {
    if (rad > SERVO1_MAX_ANGLE) {
        rad = SERVO1_MAX_ANGLE;
    } else if (rad < SERVO1_MIN_ANGLE) {
        rad = SERVO1_MIN_ANGLE;
    }
    this->radian = rad;
    int pwm = SERVO_INIT - rad * SERVO_K + SERVO_D;
    setPwm(pwm);
}

float Servo::getRadian() {
    return this->radian;
}

void Servo::setPwm(int pwm) {
    __HAL_TIM_SET_COMPARE(this->tim, this->channel, abs(pwm));
}
