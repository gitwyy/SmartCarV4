//
// Created by wangyangyang on 2021-04-10.
//

#include "robot.h"
#include "obj/Ackermann.h"
#include "util/RobotLog.h"
#include "obj/PSTwo.h"

Ackermann car;
uint32_t pre_controltime = 0;
uint32_t control_time_interval = 3000.0f;

float last_but_dist = 0.01f;
float last_but_rad = 0.01f;

// 创建手柄对象
PSTwo psTwo(PS_DI_PORT, PS_DI_PIN, PS_DO_PORT, PS_DO_PIN, PS_CS_PORT, PS_CS_PIN,
            PS_CLK_PORT, PS_CLK_PIN, PS_TIM);

void SmartcarRobotInit() {
    car.init();
    psTwo.init();
//    car.updateVel(0.3, 0);
    loginfo("smart car robot init success");
}

void SmartcarRobotTick() {
    logdebug("smart car robot tick");
    // 指定时间内 若没有新的指令到达, 则暂停小车
    if (HAL_GetTick() - pre_controltime > control_time_interval) {
        pre_controltime = HAL_GetTick();
        car.updateVel(0, 0);
    }

    car.tick();
    car.showOled();
    psTwo.tick(psTwoDriver);
}

void psTwoDriver(float butDist, float rad) {
    last_but_rad = rad;
    last_but_dist = butDist;

    car.updateVel((butDist * BUT_DIST_COE), rad);
    pre_controltime = HAL_GetTick();
    loginfo("but dist:%f, rad:%f", butDist, rad);
}
