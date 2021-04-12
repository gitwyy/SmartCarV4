//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_PSTWO_H
#define SMARTCARV4_PSTWO_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#ifdef __cplusplus

class PSTwo {
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16

#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16

#define PSS_RX 5                //��ҡ��X������
#define PSS_RY 6                //��ҡ��Y������
#define PSS_LX 7                //��ҡ��X������
#define PSS_LY 8                //��ҡ��Y������

#define PSS_OX 128              //ҡ�˵����������X
#define PSS_OY 127              //ҡ�˵����������Y
public:
    PSTwo() {};

    PSTwo(GPIO_TypeDef *di_port, uint16_t di_pin,
          GPIO_TypeDef *do_port, uint16_t do_pin,
          GPIO_TypeDef *cs_port, uint16_t cs_pin,
          GPIO_TypeDef *clk_port, uint16_t clk_pin,
          TIM_HandleTypeDef *tim);

    ~PSTwo();

private:
    GPIO_TypeDef *di_port;
    uint16_t di_pin;

    GPIO_TypeDef *do_port;
    uint16_t do_pin;

    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;

    GPIO_TypeDef *clk_port;
    uint16_t clk_pin;

    TIM_HandleTypeDef *tim;

    uint8_t data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint16_t mask[16] = {
            PSB_SELECT,
            PSB_L3,
            PSB_R3,
            PSB_START,
            PSB_PAD_UP,
            PSB_PAD_RIGHT,
            PSB_PAD_DOWN,
            PSB_PAD_LEFT,
            PSB_L2,
            PSB_R2,
            PSB_L1,
            PSB_R1,
            PSB_GREEN,
            PSB_RED,
            PSB_BLUE,
            PSB_PINK
    };    //����ֵ�밴����

    // ���ҡ�˵�ֵ
    uint8_t joystickLeftX;
    uint8_t joystickLeftY;
    // �Ҳ�ҡ�˵�ֵ
    uint8_t joystickRightX;
    uint8_t joystickRightY;
    // ���ٿصİ�ť��ֵ
    uint8_t button;

    bool isStart = false;

    uint32_t update_time = 0;

    //////////  ҡ��ת��O���������  /////////
    float lx;
    float ly;

    float rx;
    float ry;

private:
    bool isDIState();

    void setDO(bool high);

    void setCLK(bool high);

    void setCS(bool high);

    void execCmd(uint8_t cmd);

    void shortPoll();

    void enterConfig();

    void exitConfig();

    void turnOnVibrationMode();

    void turnOnAnalogMode();

    void delay(uint16_t t);

    void clearData();

    void readData();

    uint8_t readButtonData();

    uint8_t readAnalogData(uint8_t button);

public:
    void init();

    void tick(void (* driver)(float butDist, float rad));

    bool isRedLightMode();

    void setEnable(bool flag);

    /**
     * ��
     * @param left�� �������
     * @param right���Ҳ�����
     */
    void vibration(uint8_t left, uint8_t right);

    /**
     * ���Y��
     * ���ң�˵���ת����
     * @return
     */
    float getLRadian();

    /**
     * ���Y��
     * �ұ�ң�˵���ת����
     * @return
     */
    float getRRadian();

    /**
     * ���ҡ�˵ļ��� ������
     * @return
     */
    float getLLen();

    /**
     * �ұ�ҡ�˵ļ��� ������
     * @return
     */
    float getRLen();

};

#endif
#endif //SMARTCARV4_PSTWO_H
