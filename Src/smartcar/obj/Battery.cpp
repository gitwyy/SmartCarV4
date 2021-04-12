//
// Created by wangyangyang on 2021-04-10.
//

#include "Battery.h"
#include "adc.h"

Battery::Battery(double minVoltage) : minVoltage(minVoltage) {}

Battery::~Battery() {}

void Battery::init() {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 50);
}

bool Battery::isLowVoltage() {
    return this->currentValue < this->minVoltage;
}

void Battery::measureVoltage() {
    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
        double v = HAL_ADC_GetValue(&hadc1) * 3.3 * 11.1 / 4096.0;
        if (v > currentValue) {
            this->currentValue = v;
        }
    }
}

void Battery::resetMeasure() {
    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
        this->currentValue = HAL_ADC_GetValue(&hadc1) * 3.3 * 11.1 / 4096.0;
    }
}

double Battery::getVoltage() {
    return this->currentValue;
}