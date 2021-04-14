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
 * 初始化的操作
 */
void SmartcarRobotInit();

/**
 * Tick机器人心脏的跳动
 */
void SmartcarRobotTick();

/**
 * PS2 手柄驾驶小车
 * @param len 键程（表示行驶速度）
 * @param rad 摇杆角度
 */
void psTwoDriver(float len, float rad);

/**
 * 协议文件
 * 协议头
 * 协议类型
 * 协议的长度
 * 线速度
 * 角速度
 * 验证位
 * 协议结尾
 */
void update_vel(uint8_t *cmd);


/**
 * 发送机器人信息
 * 当前线速度
 * 当前角速度
 * 当前温度
 * 三轴加速度
 * 三轴角速度
 *
 */
void pushInfo();


#ifdef __cplusplus
};
#endif


#endif //SMARTCARV4_ROBOT_H
