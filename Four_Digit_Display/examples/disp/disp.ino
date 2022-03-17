#include <Wire.h>
#include <SoftwareSerial.h>
#include <Suli.h>
#include <Four_Digit_Display_Arduino.h>


Four_Digit_Display_Arduino    disp;


void setup()
{
    disp.begin(2,3);
    disp.display(1, 5);
}


void loop()
{
disp.display (0, 0);
disp.display (1, 3);
disp.display (2, 5);
disp.display (3, 9);
delay(3000);
disp.clear();
delay(2000);
}
