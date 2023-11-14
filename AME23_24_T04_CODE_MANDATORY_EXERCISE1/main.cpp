#include "mbed.h"
#include "Thermistor.h"
#include "TCI.h"
#include "Grove_LCD_RGB_Backlight.h"
#include <sstream>
#include <string>

Grove_LCD_RGB_Backlight lcd_1(D14, D15);

Thermistor thermistor(A0);
TCI tci(10, 37, A1, LED3, LED2);
// main() runs in its own thread in the OS

int main()
{
    float celsius_temp;
    float target_temp;
    lcd_1.setRGB(255, 255, 255);

    while (true) {
        ThisThread::sleep_for(500ms);
        lcd_1.locate(0, 0);

        target_temp = tci.get_target_temp();
        std::ostringstream stream;
        
        stream.precision(2);
        stream << fixed;
        stream << target_temp;


        std::string target_temp_str = "Target(C):" + stream.str();
        const char* a = (target_temp_str).c_str();
        lcd_1.print((char*) a);

        lcd_1.locate(0,1);
        
        std::ostringstream stream2;
        celsius_temp = thermistor.evaluate();

        stream2.precision(2);
        stream2 << fixed;
        stream2 << celsius_temp;

        std:string cel_temp_str = "Temp (C):" + stream2.str();
        const char* b = cel_temp_str.c_str();
        lcd_1.print((char*) b);

        char rgb = tci.update_actuators(target_temp, celsius_temp); 
        if(rgb == 0) {
            lcd_1.setRGB(255, 0, 0);
        } else{
            lcd_1.setRGB(0, 0, 255);
        }
    }
}

