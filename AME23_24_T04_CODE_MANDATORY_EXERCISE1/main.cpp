#include "mbed.h"
#include "Thermistor.h"
#include "TCI.h"
#include "Grove_LCD_RGB_Backlight.h"
#include <sstream>
#include <string>

Grove_LCD_RGB_Backlight lcd_1(D14, D15);
Thermistor thermistor(A0);
TCI tci(10, 37, A1, LED3, LED2);

// Deberia ir en el lcd, pero mejor no editarlo
void lcd_print(int row, string lcd_string, float print_value){
        lcd_1.locate(0, row);

        std::ostringstream stream;
        
        stream.precision(2);
        stream << fixed;
        stream << print_value;


        std::string target_temp_str = lcd_string  + stream.str();
        const char* a = (target_temp_str).c_str();
        lcd_1.print((char*) a);

}

int main()
{
    float celsius_temp;
    float target_temp;
    lcd_1.setRGB(255, 255, 255);
    int r,g,b;

    while (true) {
        target_temp = tci.get_target_temp();
        lcd_print(0, "Target(C):", target_temp);


        celsius_temp = thermistor.evaluate();
        lcd_print(1, "Temp(C):", celsius_temp);

        State rgb = tci.update_actuators(target_temp, celsius_temp); 
        switch(rgb){
            case State::OK:
                lcd_1.setRGB(255, 255, 255);
                break;
            case State::HEATING:
                lcd_1.setRGB(255, 0, 0);
                break;
            case State::COOLING:
                lcd_1.setRGB(0, 0, 255);
                break;
        }
        
        
    }
}
