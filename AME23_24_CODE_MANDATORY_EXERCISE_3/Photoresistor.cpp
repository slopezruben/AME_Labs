#include "Photoresistor.h"
#include "mbed.h"

Photoresistor::Photoresistor(PinName pin) : _pin(pin){
    _pin = pin;
}

float Photoresistor::evaluate(){
        unsigned short counts = _pin.read_u16();
        float Vout = counts * (5.0 / ADCres) ;
        float lux = (luxRel * (VRef * Vout - 1)) / Rl;

        lux = Photoresistor::clamp(0, lux);

        return lux;
}

float Photoresistor::clamp(float a, float b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}