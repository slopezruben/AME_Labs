#ifndef MBED_PHOTORESISTOR_H
#define MBED_PHOTORESISTOR_H

#include "mbed.h"

class Photoresistor{
    public:
        Photoresistor(PinName pin);
        float evaluate();
    private:
        unsigned short ADCres=65535;
        float Rl = 10;
        float VRef = 5;
        float luxRel = 500; 
        AnalogIn _pin;

        float clamp(float a, float b);
        };

#endif