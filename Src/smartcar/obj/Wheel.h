//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_WHEEL_H
#define SMARTCARV4_WHEEL_H

#include "Encoder.h"
#include "Motor.h"
#include "../util/PID.h"

/**
 * 轮子对象
 */
class Wheel {
private:
    /** 马达 */
    Motor *motor;
    /** 编码器 */
    Encoder *encoder;
    /** 目标速度 */
    float targetVel = 0.;
    /** 当前速度 */
    float curVel = 0.;
    /** 转速 转/秒 */
    float rev = 0.;
    /** 计时开始时间 */
    float vel_update_time = 0.;
    /** PID 算法工具 */
    PID *pid;
public:
    Wheel(Motor *motor, Encoder *encoder);


    virtual ~Wheel();

    /** 初始化 */
    void init();

    /** 更新实时速度 */
    bool updateVel();

    /**
     * 轮子转动
     * 使轮子不断逼近目标速度
     */
    void tick();

    /** 更新目标速度，车辆运行中，实时进行目标速度的更新 */
    void setTargetVel(float vel);

    /** 获取当前速度 */
    float getTargetVel();

    /** 获取当前线速度 */
    float getCurVel();

};

#endif //SMARTCARV4_WHEEL_H
