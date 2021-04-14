//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_ROBOT_H
#define SMARTCARV4_ROBOT_H

#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>
#include "stm32f1xx_hal.h"
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

/**
 * Э���ļ�
 * Э��ͷ
 * Э������
 * Э��ĳ���
 * ���ٶ�
 * ���ٶ�
 * ��֤λ
 * Э���β
 */
void update_vel(uint8_t *cmd);


/**
 * ���ͻ�������Ϣ
 * ��ǰ���ٶ�
 * ��ǰ���ٶ�
 * ��ǰ�¶�
 * ������ٶ�
 * ������ٶ�
 *
 */
void pushInfo();


#ifdef __cplusplus
};
#endif


#endif //SMARTCARV4_ROBOT_H
