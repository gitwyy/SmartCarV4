//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_CONFIG_H
#define SMARTCARV4_CONFIG_H

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


#define PI  3.1415926
//////////////// PID����ϵ�� ////////////////
#define KP 1500.0f
#define KI 0
#define KD 1000.0f


//////////////// Rate //////////////////
#define MOVE_CTRL_RATE 20
#define IMU_PUSH_RATE 20
#define VEL_PUSH_RATE 50

//////////////// ����ͨѶЭ�� ���� protocol out ////////////////////////
#define OUT_HEAD_0 0xFE
#define OUT_HEAD_1 0xCE

#define OUT_TYPE_LOG 0xF1
#define OUT_TYPE_IMU 0x11
#define OUT_TYPE_UNIVERSAL_VEL 0x12
#define OUT_TYPE_BATTERY 0x13

//////////////// ����ͨѶЭ�� ���� protocol in ////////////////////////
#define IN_HEAD_0 0xAB
#define IN_HEAD_1 0xBC

#define IN_TYPE_LED 0x01
#define IN_TYPE_BUZZER 0x02
#define IN_TYPE_MOTOR 0x21
#define IN_TYPE_UNIVERSAL_VEL 0x22
#define IN_TYPE_SERVO 0x31

//////////////// LED ////////////////////////
#define LED_PORT    GPIOE
#define LED_PIN     GPIO_PIN_10

#define IN_LED_CMD_CLOSE 0x00
#define IN_LED_CMD_OPEN 0x01
#define IN_LED_CMD_STATE 0x02

//////////////// BUZZER ////////////////////////
#define BUZZER_PORT     GPIOB
#define BUZZER_PIN      GPIO_PIN_10

#define IN_BUZZER_CMD_CLOSE 0x00
#define IN_BUZZER_CMD_OPEN 0x01
#define IN_BUZZER_CMD_STATE 0x02

////////////// SWITCH ////////////
#define SWITCH_PORT     GPIOD
#define SWITCH_PIN      GPIO_PIN_8

///////////// Motor //////////////////
#define MAX_PWM         7200
#define MIN_PWM         -7200

///////////// Motor back left //////////////////
#define MOTOR1_A_GPIO_PORT     GPIOA
#define MOTOR1_A_PIN           GPIO_PIN_3

#define MOTOR1_B_GPIO_PORT     GPIOA
#define MOTOR1_B_PIN           GPIO_PIN_2

#define MOTOR1_TIM           &htim8
#define MOTOR1_CHANNEL       TIM_CHANNEL_1

#define MOTOR1_DIRECTION    1

///////////// Motor back right //////////////////
#define MOTOR2_A_GPIO_PORT     GPIOA
#define MOTOR2_A_PIN           GPIO_PIN_4

#define MOTOR2_B_GPIO_PORT     GPIOA
#define MOTOR2_B_PIN           GPIO_PIN_5

#define MOTOR2_TIM           &htim8
#define MOTOR2_CHANNEL       TIM_CHANNEL_2

#define MOTOR2_DIRECTION    1

///////////// Encoder back left /////////////////
#define ENCODER1_TIM            &htim2
#define ENCODER1_CHANNEL        TIM_CHANNEL_ALL
#define ENCODER1_DIRECTION      -1

///////////// Encoder back right /////////////////
#define ENCODER2_TIM            &htim3
#define ENCODER2_CHANNEL        TIM_CHANNEL_ALL
#define ENCODER2_DIRECTION      1


//////////// Wheel config ///////////////////////
/** ����תһȦ���ź��� (13��������� 30�����ٱȣ�2�����±��أ�2���շ�������) */
#define WHEEL_TPR           (13 * 30 * 4)
// ���ӵ�ֱ��
#define WHEEL_DIAMETER      0.064f
// �������ӵľ���
#define WHEEL_DISTANCE      0.155f
// ǰ�����ӵ����
#define WHEEL_AXIS          0.1445f
// �ٶ����ϵ��
#define VEL_ERR_COEFFICIENT 0.000000001f

//////////// Servo 1 //////////////////////////// pe13
#define SERVO_K              622.8f
#define SERVO_D              125.8f
#define SERVO_INIT           1500
#define SERVO1_TIM           &htim1
#define SERVO1_CHANNEL       TIM_CHANNEL_1
#define SERVO1_MAX_ANGLE     (45 * PI/180)
#define SERVO1_MIN_ANGLE     (-45 * PI/180)


////////// ��� ///////////////////////////////
#define MIN_VOLTAGE         10.7
#define BATTERY_MEASURE_RATE  1
#define BATTERY_CHECK_RATE  0.1

///////// PS2 ////////////////////////////////
#define PS_DI_PORT      GPIOE
#define PS_DI_PIN       GPIO_PIN_15
#define PS_DO_PORT      GPIOD
#define PS_DO_PIN       GPIO_PIN_3
#define PS_CS_PORT      GPIOB
#define PS_CS_PIN       GPIO_PIN_13
#define PS_CLK_PORT     GPIOB
#define PS_CLK_PIN      GPIO_PIN_12
#define PS_TIM          &htim6
#define PS_CHECK_RATE   50
#define BUT_DIST_COE (1.2f/128)      // �ֱ�ҡ�˼��̶�Ӧ����ٶ�ϵ��, 30 ����ٶ�, 128 ����


///////// User Key ///////////////////////////
#define USER_KEY_PORT   GPIOD
#define USER_KEY_PIN    GPIO_PIN_8
#define USER_KEY_CHECK_RATE   20
#define MODE_LOOP_RATE  4

#ifdef __cplusplus
}
#endif

#endif //SMARTCARV4_CONFIG_H
