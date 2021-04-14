//
// Created by wangyangyang on 2021-04-10.
//

#include "PSTwo.h"
#include <Legacy/stm32_hal_legacy.h>
#include "../config/config.h"
#include "../util/RobotLog.h"
#include "math.h"

PSTwo::PSTwo(GPIO_TypeDef *di_port, uint16_t di_pin,
             GPIO_TypeDef *do_port, uint16_t do_pin,
             GPIO_TypeDef *cs_port, uint16_t cs_pin,
             GPIO_TypeDef *clk_port, uint16_t clk_pin,
             TIM_HandleTypeDef *tim) :
        di_port(di_port), di_pin(di_pin),
        do_port(do_port), do_pin(do_pin),
        cs_port(cs_port), cs_pin(cs_pin),
        clk_port(clk_port), clk_pin(clk_pin),
        tim(tim) {
}

PSTwo::~PSTwo() {}

void PSTwo::init() {
    shortPoll();
    shortPoll();
    shortPoll();
    enterConfig();
    turnOnVibrationMode();
    turnOnAnalogMode();
    exitConfig();
}

void PSTwo::setEnable(bool flag) {
    isStart = flag;
}

void PSTwo::tick(void (*driver)(float butDist, float rad)) {
    if (HAL_GetTick() - update_time < PS_CHECK_RATE) {
        return;
    }
    button = readButtonData();

    joystickLeftX = readAnalogData(PSS_LX);
    joystickLeftY = readAnalogData(PSS_LY);
    joystickRightX = readAnalogData(PSS_RX);
    joystickRightY = readAnalogData(PSS_RY);


    if (button == PSB_START) {
        HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
        HAL_Delay(500);
        HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
        isStart = !isStart;
    }
    if (!isStart) return;

    float llen = getLLen();
    float rlen = getRLen();
    float lrad = getLRadian();
    float rrad = getRRadian();

    loginfo("button:%d lx=%d ly=%d rx=%d ry=%d; llen=%f rlen=%f lrad=%f rrad=%f",
            button, joystickLeftX, joystickLeftY, joystickRightX, joystickRightY, llen, rlen, lrad, rrad);
    driver(llen, rrad);
    // ���õİ��������ж�
    switch (button) {
        case PSB_PAD_UP:
            HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
            break;
        case PSB_PAD_DOWN:
            HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
            break;
    }
    update_time = HAL_GetTick();
}

uint8_t PSTwo::readButtonData() {
    clearData();
    readData();

    uint16_t key = (data[4] << 8) | data[3];     //����16������  ����Ϊ0�� δ����Ϊ1
    for (int i = 0; i < 16; ++i) {
        if ((key & (1 << (mask[i] - 1))) == 0)
            return i + 1;
    }
    return 0; //û���κΰ�������
}

uint8_t PSTwo::readAnalogData(uint8_t button) {
    return data[button];
}


void PSTwo::readData() {
    setCS(false);
    execCmd(0x01);  //��ʼ����
    execCmd(0x42);  //��������

    for (int i = 2; i < 9; ++i) {
        for (int ref = 0x01; ref < 0x100; ref <<= 1) {
            setCLK(true);
            delay(5);
            setCLK(false);
            delay(5);
            setCLK(true);
            if (isDIState()) {
                data[i] = ref | data[i];
            }
        }
        delay(16);
    }
    setCS(true);
}

void PSTwo::clearData() {
    for (unsigned char &i : data) {
        i = 0x00;
    }
}

bool PSTwo::isRedLightMode() {
    setCS(false);
    execCmd(0x01);//��ʼ����
    execCmd(0x42);//��������
    setCS(true);

    return data[1] != 0x73;
}

void PSTwo::vibration(uint8_t left, uint8_t right) {
    setCS(false);
    delay(16);
    execCmd(0x01);//��ʼ����
    execCmd(0x42);//��������
    execCmd(0x00);
    execCmd(left);
    execCmd(right);
    execCmd(0x00);
    execCmd(0x00);
    execCmd(0x00);
    execCmd(0x00);
    setCS(true);
    delay(16);
}

void PSTwo::shortPoll() {
    setCS(false);
    delay(16);
    execCmd(0x01);//��ʼ����
    execCmd(0x42);//��������
    execCmd(0x00);
    execCmd(0x00);
    execCmd(0x00);
    setCS(true);
    delay(16);
}

void PSTwo::enterConfig() {
    setCS(false);
    delay(16);
    execCmd(0x01);
    execCmd(0x43);
    execCmd(0X00);
    execCmd(0x01);
    execCmd(0x00);
    execCmd(0X00);
    execCmd(0X00);
    execCmd(0X00);
    execCmd(0X00);
    setCS(true);
    delay(16);
}

void PSTwo::exitConfig() {
    setCS(false);
    delay(16);
    execCmd(0x01);
    execCmd(0x43);
    execCmd(0X00);
    execCmd(0x00);
    execCmd(0x5A);
    execCmd(0x5A);
    execCmd(0x5A);
    execCmd(0x5A);
    execCmd(0x5A);
    setCS(true);
    delay(16);
}

void PSTwo::turnOnVibrationMode() {
    setCS(false);
    delay(16);
    execCmd(0x01);
    execCmd(0x4D);
    execCmd(0X00);
    execCmd(0x00);
    execCmd(0X01);
    setCS(true);
    delay(16);
}

void PSTwo::turnOnAnalogMode() {
    setCS(false);
    execCmd(0x01);
    execCmd(0x44);
    execCmd(0X00);
    execCmd(0x01); //analog=0x01;digital=0x00  ������÷���ģʽ
    execCmd(0x03); //Ox03�������ã�������ͨ��������MODE������ģʽ��
    //0xEE������������ã���ͨ��������MODE������ģʽ��
    execCmd(0X00);
    execCmd(0X00);
    execCmd(0X00);
    execCmd(0X00);
    setCS(true);
    delay(16);
}

void PSTwo::setDO(bool high) {
    HAL_GPIO_WritePin(do_port, do_pin, high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void PSTwo::setCLK(bool high) {
    HAL_GPIO_WritePin(clk_port, clk_pin, high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void PSTwo::setCS(bool high) {
    HAL_GPIO_WritePin(cs_port, cs_pin, high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void PSTwo::execCmd(uint8_t cmd) {
    volatile uint16_t ref = 0x01;
    data[1] = 0;
    for (ref = 0x01; ref < 0x0100; ref <<= 1) {
        if (ref & cmd) {
            setDO(true);                   //���һλ����λ
        } else {
            setDO(false);
        }

        setCLK(true);                        //ʱ������
        delay(5);
        setCLK(false);
        delay(5);
        setCLK(true);
        if (isDIState()) {
            data[1] = ref | data[1];
        }
    }
    delay(16);
}

void PSTwo::delay(uint16_t t) {
    uint16_t differ = 0xffff - t - 5;
    /*Ϊ��ֹ���жϴ����ʱ����ɼ�������.
      ���0xfffE��ʼ��ʱ1us,�������жϴ��
     ����ʱ���������ڼ����������������0xffff��
      ��ֹͣ�����������ڴ������ֵ��������arrֵ��
      ����ʵ����ʱ(0xffff+1)t
    */
    HAL_TIM_Base_Start(tim);
            __HAL_TIM_SetCounter(tim, differ);

    while (differ < 0xffff - 5) {
        differ = __HAL_TIM_GetCounter(tim);
    }

    HAL_TIM_Base_Stop(tim);
}

bool PSTwo::isDIState() {
    return HAL_GPIO_ReadPin(di_port, di_pin) == GPIO_PIN_SET;
}

float PSTwo::getLRadian() {
    joystickLeftX = readAnalogData(PSS_LX);
    joystickLeftY = readAnalogData(PSS_LY);
    lx = -(joystickLeftX - PSS_OX);
    ly = -(joystickLeftY - PSS_OY);
    return atan2(lx, ly);
}

float PSTwo::getRRadian() {
    joystickRightX = readAnalogData(PSS_RX);
    joystickRightY = readAnalogData(PSS_RY);
    rx = -(joystickRightX - PSS_OX);
    ry = -(joystickRightY - PSS_OY);
    return atan2(rx, ry);
}

float PSTwo::getLLen() {
    joystickLeftY = readAnalogData(PSS_LY);
    return -(joystickLeftY - PSS_OY);
}

float PSTwo::getRLen() {
    joystickRightY = readAnalogData(PSS_RY);
    return -(joystickRightY - PSS_OY);
}

