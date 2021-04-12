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
    // �������
    float error = target - current;
    // �����ۼ�
    intergral += error;
    // ����������һ�����Ĳ���
    derivative = error - prevError;

    pwm += kp * error + ki * intergral + kd * derivative;
    // ��¼��һ�ε����
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

