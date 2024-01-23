#include "mbed.h"
#include "Thermistor.h"
#include "Photoresistor.h"
#include <string>
#include <iostream>

Photoresistor photores(A0);
Thermistor therm(A1);

BufferedSerial bs(D1, D0, 9600);

// main() runs in its own thread in the OS
int main()
{
    char message[14];
    bs.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
);

    while (true) {
        std::sprintf (message, "%.2f::%.2f", photores.evaluate(), therm.evaluate());
        bs.write(message, 14);
        printf("%s\n", message);
        ThisThread::sleep_for(1000ms);
    }
}

