#include "mbed.h"
#include "Thermistor.h"

Thermistor therm(A0);
// main() runs in its own thread in the OS
int main()
{
    while (true) {
        therm.evaluate();
    }
}

