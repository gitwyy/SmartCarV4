//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_ROBOT_H
#define SMARTCARV4_ROBOT_H


#ifdef __cplusplus
extern "C" {
#endif
/**
 * ��ʼ���Ĳ���
 */
void SmartcarRobotInit();

/**
 * Tick���������������
 */
void SmartcarRobotTick();

/**
 * PS2 �ֱ���ʻС��
 * @param len ���̣���ʾ��ʻ�ٶȣ�
 * @param rad ҡ�˽Ƕ�
 */
void psTwoDriver(float len, float rad);

#ifdef __cplusplus
};
#endif


#endif //SMARTCARV4_ROBOT_H
