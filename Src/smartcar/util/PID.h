//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_PID_H
#define SMARTCARV4_PID_H


class PID {
public:
    PID(float kp, float ki, float kd);

    float kp;
    float ki;
    float kd;

    float pwm = 0.0f;
    // ��һ�ε����
    float prevError = 0.0f;
    // ����
    float intergral = 0.0f;
    // ΢��
    float derivative = 0.0f;

    /**
     * pid�ļ��㺯��
     * @param target  Ŀ��ֵ
     * @param current ��ǰֵ
     * @return  pwm
     */
    float compute(float target, float current);

    /**
     *  �������е����: �����õ��ٶ� �� ��һ�β�һ��
     */
    void reset();

    void update(float kp, float ki, float kd);
};


#endif //SMARTCARV4_PID_H
