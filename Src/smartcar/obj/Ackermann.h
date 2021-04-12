//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_ACKERMANN_H
#define SMARTCARV4_ACKERMANN_H

#include "Servo.h"
#include "Wheel.h"
#include "Battery.h"
#include "Buzzer.h"

class Ackermann {
public:
    Ackermann();

    ~Ackermann();

    Servo *servo;
    Wheel *wheelL;
    Wheel *wheelR;
    Battery *battery;
    Buzzer *buzzer;

    double voltage;

public:
    void init();

    void tick();

    /**
     * ����С������ʻ�ٶ�
     * @param vel ���ٶ�
     * @param rad ת�򻡶�
     */
    void updateVel(float vel, float rad);

    /**
     * ��ȡ���ٶ�
     * @return
     */
    float getAngularVel();

    /**
     * ��ȡ���ٶ�
     * @return
     */
    float getTargetVel();

    /**
     * ��ȡ���ٶ�
     * @return
     */
    float getVel();

    /**
     * ��ʾ oled
     */
    void showOled();

    /**
     * ��ȡ���ת�򻡶�
     * @return
     */
    float getRadian();
};

#endif //SMARTCARV4_ACKERMANN_H
