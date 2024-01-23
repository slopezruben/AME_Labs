#include "Thermistor.h"
#include "mbed.h"

Thermistor::Thermistor(PinName pin) : _pin(pin){
    _pin = pin;
}

float Thermistor::evaluate(){
        float resistance = resistance_from_counts(_pin.read_u16());
        float kelvin_temp = resistance_to_kelvin(resistance);
        float celsius_temp = kelvin_to_celsius(kelvin_temp);
       
         
        return celsius_temp;
}

float Thermistor::kelvin_to_celsius(float t_kelvin){
    return t_kelvin - k;
}

float Thermistor::resistance_to_kelvin(float r_therm){
    float log_res = log(r_therm / r0);
    return 1 / ( (( log_res / beta) + 1) / t0);
}

float Thermistor::resistance_from_counts(unsigned short counts){
    return rb * (((float) ADCres / ((float) counts )) - 1 );
}