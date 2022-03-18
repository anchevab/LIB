// KeyPad_Demo_3x3 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of most of the library functions.
// Open the serial monitor (115200 baud) to see the output.
//
// IBridge Lite:  3 x 3
//    Cols: 5, 6, 7
//    Rows: 2, 3, 4

// Include our library :)
#include <KeyPad.h>

// Setup for a 4x4 keypad
KeyPad  myKeys(3, 3);

void setup()
{
  myKeys.setColPins(5, 6, 7);
  myKeys.setRowPins(2, 3, 4);
  myKeys.setDebounceDelay(50);
  
  Serial.begin(115200);
}

void loop()
{
  char key;
  
  key = myKeys.readKeys();
  if (key != 0)
    Serial.print(key);
}
