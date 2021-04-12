//
// Created by wangyangyang on 2021-04-10.
//

#ifndef SMARTCARV4_BATTERY_H
#define SMARTCARV4_BATTERY_H

#ifdef __cplusplus

class Battery {
public:
    Battery(double minVoltage);

    ~Battery();

private:
    double minVoltage;
    double currentValue;

public:
    void init();

    bool isLowVoltage();

    double getVoltage();

    void measureVoltage();

    void resetMeasure();

};

#endif

#endif //SMARTCARV4_BATTERY_H
