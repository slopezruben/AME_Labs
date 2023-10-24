#include "mbed.h"
#include "Photoresistor.h"

// main() runs in its own thread in the OS
Photoresistor photores(A0);

int main()
{
    while (true) {
        photores.evaluate();
    }
}

