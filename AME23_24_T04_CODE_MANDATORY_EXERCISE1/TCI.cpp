#include "TCI.h"
#include "mbed.h"

TCI::TCI(float max, float min, PinName pin, PinName heater, PinName ac_cooler) :  _pin(pin), _heater(heater),  _ac_cooler(ac_cooler){
    min_temp = min;
    max_var_temp = max - min;
    _pin = pin;

    current_actuator = NULL;
    previous_state = State::OK;
    current_state = State::OK;
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

State TCI::update_actuators(float target, float read){
    State next_state;
    heater_intensity = target - read / max_var_temp;

    switch(current_state){
        case State::OK:
            next_state = State::OK;
            if ((target ) < (read * 0.9)){
                next_state = State::COOLING;
            }else if (target  > (read * 1.1)){
                next_state = State::HEATING;
            }
            break;
        case State::COOLING:
            next_state = State::COOLING;
            if(target > read){
                next_state = State::OK;
            }
            break;
        case State::HEATING:
            next_state = State::HEATING;
            if(target < read){
                next_state = State::OK;
            }
            break;
    }
    
    exit_state();
    enter_state(next_state);
    return next_state;
}

void TCI::exit_state(){
    previous_state = current_state;
    flip();
    current_actuator = NULL;
}
/*

void TCI::heater2_on(){
   _heater2.write(heater_intensity);
}

void TCI::heater2_off(){
   _heater2.write(0);
}*/

void TCI::enter_state(State state){
    current_state = state;
        switch(previous_state){
        case HEATING:
            current_actuator = &_heater;
            //heater2_on();
            flip();
            break;
        case COOLING:
            //heater2_off(); //TODO cuando salga del estado
            current_actuator = &_ac_cooler;
            flip();
            flip();
            flip();
            break;
        case OK:
            break;
        default:
            break;
    }
}

