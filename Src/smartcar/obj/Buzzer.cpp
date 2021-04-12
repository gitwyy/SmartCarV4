//
// Created by wangyangyang on 2021-04-10.
//

#include "Buzzer.h"

Buzzer::Buzzer(GPIO_TypeDef *port, uint16_t pin) : port(port), pin(pin) {}

Buzzer::~Buzzer() {}

void Buzzer::open() {
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void Buzzer::close() {
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

void Buzzer::toggle() {
    HAL_GPIO_TogglePin(port, pin);
}

bool Buzzer::isOpen() {
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
}