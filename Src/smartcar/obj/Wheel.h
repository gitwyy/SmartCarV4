//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_WHEEL_H
#define SMARTCARV4_WHEEL_H

#include "Encoder.h"
#include "Motor.h"
#include "../util/PID.h"

/**
 * ���Ӷ���
 */
class Wheel {
private:
    /** ��� */
    Motor *motor;
    /** ������ */
    Encoder *encoder;
    /** Ŀ���ٶ� */
    float targetVel = 0.;
    /** ��ǰ�ٶ� */
    float curVel = 0.;
    /** ת�� ת/�� */
    float rev = 0.;
    /** ��ʱ��ʼʱ�� */
    float vel_update_time = 0.;
    /** PID �㷨���� */
    PID *pid;
public:
    Wheel(Motor *motor, Encoder *encoder);


    virtual ~Wheel();

    /** ��ʼ�� */
    void init();

    /** ����ʵʱ�ٶ� */
    bool updateVel();

    /**
     * ����ת��
     * ʹ���Ӳ��ϱƽ�Ŀ���ٶ�
     */
    void tick();

    /** ����Ŀ���ٶȣ����������У�ʵʱ����Ŀ���ٶȵĸ��� */
    void setTargetVel(float vel);

    /** ��ȡ��ǰ�ٶ� */
    float getTargetVel();

    /** ��ȡ��ǰ���ٶ� */
    float getCurVel();

};

#endif //SMARTCARV4_WHEEL_H
