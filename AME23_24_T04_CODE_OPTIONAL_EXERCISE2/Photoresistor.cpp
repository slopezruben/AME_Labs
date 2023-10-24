#include "Photoresistor.h"
#include "mbed.h"

Photoresistor::Photoresistor(PinName pin) : _pin(pin){
    _pin = pin;
}

void Photoresistor::evaluate(){
        unsigned short counts = _pin.read_u16();
        printf("Counts: %d\n", counts);
        float Vout = counts * (3.3 / ADCres) ;
        printf("Voltage: %.2f\n", Vout);
        float lux = (luxRel * (VRef * Vout - 1)) / Rl;

        lux = Photoresistor::clamp(0, lux);

        printf("Lux: %.2f\n", lux);
        ThisThread::sleep_for(1s);
}

float Photoresistor::clamp(float a, float b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}