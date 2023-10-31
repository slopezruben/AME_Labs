#include "mbed.h"
#include "Thermistor.h"
#include "TCI.h"
#include "Grove_LCD_RGB_Backlight.h"

Grove_LCD_RGB_Backlight lcd_1(D14, D15);

Thermistor thermistor(A0);
TCI tci(10, 37, A1);
// main() runs in its own thread in the OS
int main()
{
    float celsius_temp;
    float target_temp;
    while (true) {
        celsius_temp = thermistor.evaluate();
        //printf("Temperature (Cº): %.2f\n", celsius_temp);
    
        target_temp = tci.get_target_temp();
       // printf("Target Temperature (Cº): %.2f\n", target_temp);

       lcd_1.setRGB(255, 255, 255);

    }
}

