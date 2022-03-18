/*
 * Simple hello world program.
 */
#include <Lcd.h>

// LCD module is 16 columns wide
// 8 pin mode (see README for default pin numbers)
Lcd lcd = Lcd(16, FUNCTION_8BIT);

char msg[] = "Hello, World!";

void setup()
{
  lcd.setup();  // setup arduino pins and initialize LCD
}

void loop()
{
  lcd.home();     // return cursor to home possition
  lcd.print(msg); // print the ever so familiar message
}

