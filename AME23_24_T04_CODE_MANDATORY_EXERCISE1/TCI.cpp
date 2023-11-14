#include "TCI.h"
#include "mbed.h"

TCI::TCI(float max, float min, PinName pin, PinName heater, PinName ac_cooler) :  _pin(pin), _heater(heater),  _ac_cooler(ac_cooler){
    min_temp = min;
    max_var_temp = max - min;
    _pin = pin;
    current_actuator = NULL;
}

float TCI::get_target_temp(){
    float target_temp = min_temp + _pin.read_u16() * (max_var_temp / ADCres);
    return target_temp;
}

void TCI::flip(){
    if(current_actuator != NULL){
        float a = current_actuator->read();
        current_actuator->write(!a);
    }
}

//TODO: Debouncing + NULL (White) Status
char TCI::update_actuators(float target, float read){
    if(target < read){
        if (current_actuator == &_ac_cooler) return 1;
        flip();
        current_actuator = &_ac_cooler;
        flip();
        return 1;
    }else{
        if (current_actuator == &_heater) return 0;
        flip();
        current_actuator = &_heater;
        flip();
        return 0;
    }
}