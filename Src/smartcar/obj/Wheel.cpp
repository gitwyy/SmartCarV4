//
// Created by wangyangyang on 2021-04-10.
//

#include "Wheel.h"
#include "../util/RobotLog.h"
#include "../config/config.h"
#include "math.h"

Wheel::Wheel(Motor *motor, Encoder *encoder) {
    this->motor = motor;
    this->encoder = encoder;
    this->pid = new PID(KP, KI, KD);
}

void Wheel::init() {
    this->encoder->init();
    this->motor->init();
    loginfo("wheel init success");
}

void Wheel::tick() {
    if (this->updateVel()) {
        float pwm = this->pid->compute(this->targetVel, this->curVel);
        this->motor->spin(pwm);
        loginfo("vel=%f tar=%f pwm=%f \r\n", curVel, targetVel, pwm);
    }
}


void Wheel::setTargetVel(float vel) {
    // 要让轮子转动到指定的目标速度: PID  闭环控制, 轮子当前的速度
    if (abs(targetVel - vel) >= VEL_ERR_COEFFICIENT) {
        this->pid->reset();
        this->targetVel = vel;
        logdebug("reset pid, curr vel: %f, target vel: %f", this->curVel, this->targetVel);
    }
}

float Wheel::getTargetVel() {
    return this->targetVel;
}

/**
 * 计算速度 m/s:
 *      count/一圈的数量 => 圈数
 *  圈数转成距离:   圈数 * 轮子的周长 =  圈数 * ( 3.14 * 轮子的直径)  ==> m  D
 *  单位时间:   1000/MOVE_CTRL_RATE ms
 *  速度:    D/单位时间 ===>  D/1000/MOVE_CTRL_RATE  m/ms ===> m/s
 *                           D*MOVE_CTRL_RATE/1000 ===> D*MOVE_CTRL_RATE
 *         圈数 * ( 3.14 * 轮子的直径)*MOVE_CTRL_RATE
 *         count/一圈的数量 * ( 3.14 * 轮子的直径)*MOVE_CTRL_RATE
 */
bool Wheel::updateVel() {
    // 单位时间内测量轮子的转速: 每隔1000/MOVE_CTRL_RATE 计算一次轮子的转速
    uint32_t curr_time = HAL_GetTick();
    uint32_t unit_time = curr_time - vel_update_time;
    if (unit_time >= (1000 / MOVE_CTRL_RATE)) {
        short count = this->encoder->read();
        // 转速 = （一个计时单位信号数 / 每圈信号数 / 计时单位转成秒数 = 每秒的圈数）
        this->rev = (double) count / WHEEL_TPR / ((double) unit_time / 1000.0);
        // 实时速度 = 转速 * 轮子的周长
        this->curVel = this->rev * PI * WHEEL_DIAMETER;
        vel_update_time = curr_time;
        return true;
    }
    return false;
}

float Wheel::getCurVel() {
    return this->curVel;
}

Wheel::~Wheel() {
    delete this->motor;
    delete this->encoder;
    delete this->pid;
}