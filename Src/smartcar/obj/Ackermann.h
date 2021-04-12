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
     * 更新小车的行驶速度
     * @param vel 线速度
     * @param rad 转向弧度
     */
    void updateVel(float vel, float rad);

    /**
     * 获取角速度
     * @return
     */
    float getAngularVel();

    /**
     * 获取角速度
     * @return
     */
    float getTargetVel();

    /**
     * 获取线速度
     * @return
     */
    float getVel();

    /**
     * 显示 oled
     */
    void showOled();

    /**
     * 获取舵机转向弧度
     * @return
     */
    float getRadian();
};

#endif //SMARTCARV4_ACKERMANN_H
