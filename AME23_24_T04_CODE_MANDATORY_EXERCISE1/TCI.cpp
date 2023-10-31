#include "TCI.h"
#include "mbed.h"

TCI::TCI(float max, float min, PinName pin) : _pin(pin){
    min_temp = min;
    max_var_temp = max - min;
    _pin = pin;
}

float TCI::get_target_temp(){
    float target_temp = min_temp + _pin.read_u16() * (max_var_temp / ADCres);
    return target_temp;
}