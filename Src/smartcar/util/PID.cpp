//
// Created by wangyangyang on 2021-04-10.
//

#include "PID.h"
#include <cstdio>

PID::PID(float kp, float ki, float kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

float PID::compute(float target, float current) {
    // 计算误差
    float error = target - current;
    // 误差的累计
    intergral += error;
    // 本次误差和上一次误差的差异
    derivative = error - prevError;

    pwm += kp * error + ki * intergral + kd * derivative;
    // 记录上一次的误差
    prevError = error;

    return pwm;
}


void PID::update(float kp, float ki, float kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->reset();
}

void PID::reset() {
    intergral = 0.0f;
    derivative = 0.0f;
    prevError = 0.0f;
}

