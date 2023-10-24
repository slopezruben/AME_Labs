#ifndef MBED_THERMISTOR_H
#define MBED_THERMISTOR_H

#include "mbed.h"

class Thermistor{
    public:
        Thermistor(PinName pin);
        void evaluate();
    private:
        unsigned short ADCres = 65535;
        int beta = 4250;
        int rb = 100000;
        int r0 = 100000;
        float t0 = 298.15;
        float k = 273.15;
        AnalogIn _pin;
        
        float kelvin_to_celsius(float k_temp);
        float resistance_to_kelvin(float r_therm);
        float resistance_from_counts(unsigned short counts);
};

#endif