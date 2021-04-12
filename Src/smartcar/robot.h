//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_ROBOT_H
#define SMARTCARV4_ROBOT_H


#ifdef __cplusplus
extern "C" {
#endif
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

#ifdef __cplusplus
};
#endif


#endif //SMARTCARV4_ROBOT_H
