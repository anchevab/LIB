/*
 * Define custom characters for creating an animation
 */
#include <Lcd.h>

#define LCD_WIDTH 16                     // number of columns in LCD module
Lcd lcd = Lcd(LCD_WIDTH, FUNCTION_4BIT); // use 4 pin mode

// x x x 1 1 1 1 1
// x x x 1 0 0 0 0
// x x x 1 0 0 0 0
// x x x 1 0 0 0 0
// x x x 1 0 0 0 0
// x x x 1 0 0 0 0
// x x x 1 1 1 1 1
// x x x 0 0 0 0 0
uint8_t left[] = { 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00 };
  
// x x x 1 1 1 1 1
// x x x 0 0 0 0 1
// x x x 0 0 0 0 1
// x x x 0 0 0 0 1
// x x x 0 0 0 0 1
// x x x 0 0 0 0 1
// x x x 1 1 1 1 1
// x x x 0 0 0 0 0
uint8_t right[] = { 0x1F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1F, 0x00 };
  
// x x x 1 1 1 1 1
// x x x 0 0 0 0 0
// x x x 0 0 0 0 0
// x x x 0 0 0 0 0
// x x x 0 0 0 0 0
// x x x 0 0 0 0 0
// x x x 1 1 1 1 1
// x x x 0 0 0 0 0
uint8_t middle_empty[] = { 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00 };

// x x x 1 1 1 1 1
// x x x 0 0 0 0 0
// x x x 0 1 1 1 0
// x x x 1 1 1 1 1
// x x x 0 1 1 1 0
// x x x 0 0 0 0 0
// x x x 1 1 1 1 1
// x x x 0 0 0 0 0
uint8_t middle_full[] = { 0x1F, 0x00, 0x0E, 0x1F, 0x0E, 0x00, 0x1F, 0x00 };

int pos = 0; // current position of animated blip
int max_pos = LCD_WIDTH-3;
int dir = 1; // 1 -> blip is moving to the right, -1 -> to the left

void init_animation()
{
  lcd.home();
  lcd.print((char)0);   // draw left part of bar
  
  for(int i=0; i<(LCD_WIDTH-2); i++)
    lcd.print((char)2); // draw middle section
  
  lcd.print((char)1);   // draw right part of bar
  
  lcd.move_to(2,1);     // return cursor to starting pos
  lcd.print((char)3);   // and draw first char in animation
  pos = 1;
}

void animate()
{
  lcd.shift(SHIFT_CURSOR | (dir == 1? SHIFT_LEFT : SHIFT_RIGHT));
  lcd.print((char)2);
  
  lcd.print((char)3);

  if (pos == max_pos && dir == 1) {
    dir = -1;
    lcd.entry_mode(ENTRY_CURSOR_DEC);
    lcd.shift(SHIFT_CURSOR | SHIFT_LEFT);
    lcd.shift(SHIFT_CURSOR | SHIFT_LEFT);
  } else if (pos == 0 && dir == -1) {
    dir = 1;
    lcd.entry_mode(ENTRY_CURSOR_INC);
    lcd.shift(SHIFT_CURSOR | SHIFT_RIGHT);
    lcd.shift(SHIFT_CURSOR | SHIFT_RIGHT);
  }

  pos = pos + dir;
}

void setup()
{
  // set pin assignment
  lcd.set_ctrl_pins(CTRLPINS(11,10,9)); // RS->11, RS->10, E->9
  lcd.set_data_pins(_4PINS(4,3,2,1));   // D4->4, D5->5, D6->6, D7->7
  
  lcd.setup(); // setup arduino and initialize LCD
  
  // define the custom characters
  lcd.define_char(0, left);
  lcd.define_char(1, right);
  lcd.define_char(2, middle_empty);
  lcd.define_char(3, middle_full);
  
  init_animation();
}

void loop()
{
  delay(175);
  animate();
}

