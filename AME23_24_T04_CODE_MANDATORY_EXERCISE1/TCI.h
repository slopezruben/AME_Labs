#ifndef MBED_TCI_H
#define MBED_TCI_H

#include "mbed.h"

class TCI{
    public:
        TCI(float max, float min, PinName pin);
        float get_target_temp();
    private:
        unsigned short ADCres = 65535;
        float max_var_temp, min_temp;
        AnalogIn _pin;
};

#endif