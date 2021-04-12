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
    // Ҫ������ת����ָ����Ŀ���ٶ�: PID  �ջ�����, ���ӵ�ǰ���ٶ�
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
 * �����ٶ� m/s:
 *      count/һȦ������ => Ȧ��
 *  Ȧ��ת�ɾ���:   Ȧ�� * ���ӵ��ܳ� =  Ȧ�� * ( 3.14 * ���ӵ�ֱ��)  ==> m  D
 *  ��λʱ��:   1000/MOVE_CTRL_RATE ms
 *  �ٶ�:    D/��λʱ�� ===>  D/1000/MOVE_CTRL_RATE  m/ms ===> m/s
 *                           D*MOVE_CTRL_RATE/1000 ===> D*MOVE_CTRL_RATE
 *         Ȧ�� * ( 3.14 * ���ӵ�ֱ��)*MOVE_CTRL_RATE
 *         count/һȦ������ * ( 3.14 * ���ӵ�ֱ��)*MOVE_CTRL_RATE
 */
bool Wheel::updateVel() {
    // ��λʱ���ڲ������ӵ�ת��: ÿ��1000/MOVE_CTRL_RATE ����һ�����ӵ�ת��
    uint32_t curr_time = HAL_GetTick();
    uint32_t unit_time = curr_time - vel_update_time;
    if (unit_time >= (1000 / MOVE_CTRL_RATE)) {
        short count = this->encoder->read();
        // ת�� = ��һ����ʱ��λ�ź��� / ÿȦ�ź��� / ��ʱ��λת������ = ÿ���Ȧ����
        this->rev = (double) count / WHEEL_TPR / ((double) unit_time / 1000.0);
        // ʵʱ�ٶ� = ת�� * ���ӵ��ܳ�
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