/*
 * Simple hello world program in 4 pin mode.
 */
#include <Lcd.h>

// LCD module is 16 columns wide, use 4 pin mode
Lcd lcd = Lcd(16, FUNCTION_4BIT);

char msg[] = "Hello, World!";

void setup()
{
  // for the sake of demonstration change pin assignment
  lcd.set_ctrl_pins(CTRLPINS(1,2,3)); // RS->1, RW->2, E->3
  lcd.set_data_pins(_4PINS(4,5,6,7)); // D4->4, D5->5, D6->6, D7->7
  
  lcd.setup();  // setup arduino and initialize LCD
}

void loop()
{
  lcd.home();     // return cursor to home possition
  lcd.print(msg); // print the ever so familiar message
}

