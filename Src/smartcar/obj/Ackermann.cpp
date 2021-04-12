//
// Created by wangyangyang on 2021-04-10.
//

#include "Ackermann.h"
#include "math.h"
#include "oled.h"

/**
 * 构建阿克曼结构的小车
 */
Ackermann::Ackermann() {
    Motor *motorL = new Motor(MOTOR1_A_GPIO_PORT, MOTOR1_A_PIN, MOTOR1_B_GPIO_PORT, MOTOR1_B_PIN, MOTOR1_TIM,
                              MOTOR1_CHANNEL, MOTOR1_DIRECTION);
    Encoder *encoderL = new Encoder(ENCODER1_TIM, ENCODER1_CHANNEL, ENCODER1_DIRECTION);
    this->wheelL = new Wheel(motorL, encoderL);

    Motor *motorR = new Motor(MOTOR2_A_GPIO_PORT, MOTOR2_A_PIN, MOTOR2_B_GPIO_PORT, MOTOR2_B_PIN, MOTOR2_TIM,
                              MOTOR2_CHANNEL, MOTOR2_DIRECTION);
    Encoder *encoderR = new Encoder(ENCODER2_TIM, ENCODER2_CHANNEL, ENCODER2_DIRECTION);
    this->wheelR = new Wheel(motorR, encoderR);

    this->servo = new Servo(SERVO1_TIM, SERVO1_CHANNEL);

    this->battery = new Battery(11.0);
    this->buzzer = new Buzzer(BUZZER_PORT, BUZZER_PIN);
}

Ackermann::~Ackermann() {
    delete this->wheelL;
    delete this->wheelR;
    delete this->servo;
    delete this->battery;
    delete this->buzzer;
}

void Ackermann::init() {
    this->wheelL->init();
    this->wheelR->init();
    this->servo->init();
    OLED_Init();
    this->buzzer->open();
    HAL_Delay(500);
    this->buzzer->close();
}

void Ackermann::tick() {
    wheelL->tick();
    wheelR->tick();
}

void Ackermann::updateVel(float vel, float rad) {
    this->servo->setRadian(rad);
//    float velL = vel * (1 - WHEEL_DISTANCE * tan(rad) / (2 * WHEEL_AXIS));
//    float velR = vel * (1 + WHEEL_DISTANCE * tan(rad) / (2 * WHEEL_AXIS));

    //左边轮子速度
    float velL = vel - rad * 0.5 * WHEEL_DISTANCE;
    //右边轮子速度
    float velR = vel + rad * 0.5 * WHEEL_DISTANCE;

    this->wheelL->setTargetVel(velL);
    this->wheelR->setTargetVel(velR);
}

float Ackermann::getVel() {
    float velL = wheelL->getCurVel();
    float velR = wheelR->getCurVel();

    return (velL + velR) / 2;
}

float Ackermann::getAngularVel() {
    float velL = wheelL->getCurVel();
    float velR = wheelR->getCurVel();

    return (-velL + velR) / (2 * WHEEL_DISTANCE * 0.5);
}

float Ackermann::getTargetVel() {
    return (this->wheelL->getTargetVel() + this->wheelR->getTargetVel()) / 2;
}

void Ackermann::showOled() {
    uint8_t msg[] = "smart ackerman";
    OLED_ShowString(0, 0, msg);

    this->battery->measureVoltage();
    this->voltage = battery->getVoltage();

    OLED_ShowString(0, 12, (uint8_t *) "Vol:");
    OLED_ShowNumber(36, 12, int(voltage * 10), 3, 12);

    // 显示100倍的PID
    OLED_ShowString(0, 24, (uint8_t *) "P:");
    OLED_ShowNumber(12, 24, KP, 4, 12);

    OLED_ShowString(48, 24, (uint8_t *) "I:");
    OLED_ShowNumber(60, 24, KI, 3, 12);

    OLED_ShowString(84, 24, (uint8_t *) "D:");
    OLED_ShowNumber(96, 24, KD, 4, 12);

    // 显示 目标速度， 舵机转向角度
    OLED_ShowString(0, 36, (uint8_t *) "tv:");
    OLED_ShowNumber(24, 36, (this->getTargetVel() * 100), 4, 12);
    OLED_ShowString(72, 36, (uint8_t *) "rd:");
    OLED_ShowNumber(96, 36, abs(this->getRadian() * 100), 4, 12);

    // 当前速度和角速度
    OLED_ShowString(0, 48, (uint8_t *) "cv:");
    OLED_ShowNumber(24, 48, abs((this->getVel() * 100)), 4, 12);
    OLED_ShowString(72, 48, (uint8_t *) "rv:");
    OLED_ShowNumber(96, 48, abs((this->getAngularVel() * 100)), 4, 12);

    // 刷新屏幕
    OLED_Refresh_Gram();
}

float Ackermann::getRadian() {
    return this->servo->getRadian();
}
