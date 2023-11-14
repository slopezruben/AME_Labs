#ifndef MBED_TCI_H
#define MBED_TCI_H

#include "mbed.h"

class TCI{
    public:
        TCI(float max, float min, PinName pin, PinName heater, PinName ac_cooler);
        float get_target_temp();
        char update_actuators(float target, float read);
        void flip();

    private:
        unsigned short ADCres = 65535;
        float max_var_temp, min_temp;
        AnalogIn _pin;
        
        DigitalOut _heater;
        DigitalOut _ac_cooler;

        DigitalOut* current_actuator;
};

#endif