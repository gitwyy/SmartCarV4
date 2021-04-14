//
// Created by wangyangyang on 2021-04-10.
//

#include "robot.h"
#include "obj/Ackermann.h"
#include "util/RobotLog.h"
#include "obj/PSTwo.h"
#include "obj/Buzzer.h"
#include "config/protocol.h"
#include "util/common_uart.h"
#include "lib/mpu9250.h"
#include <string.h>

Ackermann car;
uint32_t pre_controltime = 0;
uint32_t lastPublishTime = 0;
uint32_t control_time_interval = 3000.0f;

// �����ֱ�����
PSTwo psTwo(PS_DI_PORT, PS_DI_PIN, PS_DO_PORT, PS_DO_PIN, PS_CS_PORT, PS_CS_PIN,
            PS_CLK_PORT, PS_CLK_PIN, PS_TIM);

void SmartcarRobotInit() {
    car.init();
    psTwo.init();
    logdebug("smart car robot init success");
}

void SmartcarRobotTick() {
    logdebug("smart car robot tick");
    // ָ��ʱ���� ��û���µ�ָ���, ����ͣС��
    if (HAL_GetTick() - pre_controltime > control_time_interval) {
        pre_controltime = HAL_GetTick();
        car.updateVel(0, 0);
    }

    car.tick();
    car.showOled();
    psTwo.tick(psTwoDriver);
//    pushInfo();
}

void psTwoDriver(float butDist, float rad) {
    car.updateVel((butDist * BUT_DIST_COE), rad);
    pre_controltime = HAL_GetTick();
    logdebug("pstwo driver but dist:%f, rad:%f", butDist, rad);
}

void commonDriver(float vel, float rad) {
    car.updateVel(vel, rad);
    pre_controltime = HAL_GetTick();
    logdebug("common driver vel:%f, rad:%f", vel, rad);
}

/**
 * �����ж� ���ݽ��ջص�
 *
 * @param receive_buf
 * @param receive_len
 * @see config/protocol.h
 */
void common_uart_idle_callback(uint8_t receive_buf[], uint16_t receive_len) {
    loginfo(">>>>>>>>>>>>>>>>>>>>>>>>>>>>> %d, %s", receive_len, receive_buf);
    if (receive_len < 4) return;
    int i = 0;
    while (i < receive_len) {
        uint8_t head0 = receive_buf[i];
        if (head0 != FLAG_HEAD0) continue;
        uint8_t head1 = receive_buf[i + 1];
        if (head1 != FLAG_HEAD1) continue;

        uint8_t data_type = receive_buf[i + 2];

        uint8_t data_len = receive_buf[i + 3];
        if (receive_len < data_len) return;

        uint8_t tail = receive_buf[i + data_len - 1];
        if (tail != FLAG_TAIL) return;

        auto cmd = new uint8_t[data_len];
        memcpy(cmd, receive_buf + i, data_len);
        if (data_type == TYPE_UPDATE_VEL) {
            update_vel(cmd);
        }
        delete cmd;
    }
}

/**
 * Э���ļ�
 * Э��ͷ��2λ��
 * Э�����ͣ�1λ��
 * ���ݵĳ��ȣ�1λ��
 * ******** С���Ŵ���1000����ʹ��ʱ��Ҫ���� **********
 * ���ٶȣ�short 2λ��
 * ���ٶȣ�short 2λ��
 * ������֤λ
 * Э���β
 */
void update_vel(uint8_t cmd[]) {
    car.buzzer->toggle();
    uint8_t vel_low = cmd[4];
    uint8_t vel_high = cmd[5];
    short vel = vel_high << 8 | vel_low;
    float V = (float) vel / 1000;

    uint8_t angular_low = cmd[6];
    uint8_t angular_high = cmd[7];
    short angular = angular_high << 8 | angular_low;
    float W = (float) angular / 1000;

    commonDriver(V, W);
}

void pushInfo() {
    if (HAL_GetTick() - lastPublishTime < 50) {
        return;
    }
    lastPublishTime = HAL_GetTick();
    short temp = MPU_Get_Temperature();

    short ax, ay, az = 0;
    MPU_Get_Accelerometer(&ax, &ay, &az);

    short gx, gy, gz = 0;
    MPU_Get_Gyroscope(&gx, &gy, &gz);

    short mx, my, mz = 0;
    MPU_Get_Magnetometer(&mx, &my, &mz);

    struct TXProtocol *protocol = new TXProtocol;
    uint8_t protocolLength = sizeof(TXProtocol);
    protocol->head0 = FLAG_HEAD0;
    protocol->head1 = FLAG_HEAD1;
    protocol->type = TYPE_UPLOAD;
    protocol->len = protocolLength;

    // �¶�
    protocol->temperature = temp;

    // ������ٶ�
    protocol->ax = ax;
    protocol->ay = ay;
    protocol->az = az;
    // ������ٶ�
    protocol->gx = gx;
    protocol->gy = gy;
    protocol->gz = gz;
    // ����ش�
    protocol->mx = mx;
    protocol->my = my;
    protocol->mz = mz;

    // ���ٶ�
    short V = (short) (car.getVel() * 1000);
    protocol->velocity = V;

    // ���ٶ�
    short W = (short) (car.getAngularVel() * 1000);
    protocol->angular = W;

    // ֡β
    protocol->tail = FLAG_TAIL;
    // ����λ����Ϣ���ͳ�ȥ
    common_uart_send((uint8_t *) protocol, protocolLength);

    delete protocol;
}
