#ifndef MBED_TCI_H
#define MBED_TCI_H

#include "mbed.h"

enum State{
  HEATING = 0xFF0000,
  COOLING = 0x0000FF,
  OK  = 0xFFFFFF
};

class TCI{
    public:
        TCI(float max, float min, PinName pin, PinName heater, PinName ac_cooler);
        float get_target_temp();
        State update_actuators(float target, float read);
        void flip();

    private:
        
        unsigned short ADCres = 65535;
        float max_var_temp, min_temp, heater_intensity;
        AnalogIn _pin;

        State previous_state, current_state;
        void exit_state();
        void enter_state(State state);
        //void heater2_on();
        // void heater2_off();

        DigitalOut _heater;
        DigitalOut _ac_cooler;

        DigitalOut* current_actuator;
};

#endif