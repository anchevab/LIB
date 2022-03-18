/*
Td5Hmi.cpp -
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
*/

#include <MemoryFree.h>
//#include <Stdio.h>
#include "td5hmi.h"
#include "td5comm.h"
#include "td5strings.h"

static byte brightness = 0;

// Initialize buttons
Button btn_up(keyPadButtonsPin, HIGH, 850);
Button btn_down(keyPadButtonsPin, HIGH, 400);
Button btn_left(keyPadButtonsPin, HIGH, 550);
Button btn_right(keyPadButtonsPin, HIGH, 700);
Button btn_enter(keyPadButtonsPin, HIGH, 200);
Button btn_quit(keyPadButtonsPin, HIGH, 50);
Button btn_powerup(keyPadPowerPin, LOW);
Button *btns[]={
  &btn_up,&btn_down,&btn_left,&btn_right,&btn_enter,&btn_quit, &btn_powerup};

ParamList fuellingParams(0, 1, 19, 22, 3, (char**)&fuelling_params, 14, (char**)&fuelling_values, 5, btns);
ParamList optionsParams(0, 1, 19, 3, 3, (char**)&options_params, 14, (char**)&options_values, 5, btns);

extern LiquidCrystal lcd;

// Class Hmi
Hmi::Hmi(byte c, byte r, byte l)
{
  col = c;
  row = r;
  length = l;
}

// Class LcdBacklight

LcdBacklight::LcdBacklight(byte pinBkLight)
{
  pin = pinBkLight;
  pinMode(pin, OUTPUT);
  brightness = 0;  
}

void LcdBacklight::incBrightness(byte inc)
{
  if((brightness + inc) <= 100)
  {
    brightness += inc;
  }
  update();
}

void LcdBacklight::decBrightness(byte dec)
{
  if((brightness-dec)>=0)
  {
    brightness -= dec;
  }
  update();
}

void LcdBacklight::update()
{
  on();  
}

void LcdBacklight::setBrightness(byte br)
{
  brightness = br;
}

void LcdBacklight::on()
{
#if  defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  analogWrite(pin, 160-((brightness/10))*12); 
#endif
  
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  analogWrite(pin, 60+((brightness/10)*12)); 
#endif
}

void LcdBacklight::off()
{
#if  defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  analogWrite(pin, 255); 
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  analogWrite(pin, 0); 
#endif
}


// Class ProgBar
ProgBar::ProgBar(byte c, byte r, byte l, byte bmin , byte bmax):
Hmi(c, r, l)
{
  advance = 0;
  ratio = (float)((float)l / (float)(bmax - bmin));
}

void ProgBar::show()
{
  // here we should save the current screen

  lcd.setCursor(col, row);
  for(int i = col; i < length; i++)
  {
    lcd.setCursor(col, row);
    lcd.write(254);
  }
}

void ProgBar::hide()
{
  // here we should restore the current screen

  show();
}


void ProgBar::update(byte progr)
{
  byte curr_adv = ((float)progr * ratio);
  if(advance != curr_adv)
  {
    lcd.setCursor(col, row);
    for(int i = col; i < length; i++)
    {
      lcd.write((i > curr_adv ? 254 : 255));
    }
    advance = curr_adv;
  }
}


  
// Class ScrollBarV
ScrollBarV::ScrollBarV(byte c, byte r, byte h):
Hmi(c, r, 1)
{
  v_height = h;
}

void ScrollBarV::update(byte progr)
{
  int mapped;
  if (progr>99) 
  {
    progr=99;
  }	
  mapped=(int)(v_height*2-2)*progr/100; // This is mapped position, 2 per row of bar.
  for (byte i=0;i<v_height;i++)
  {
    lcd.setCursor(col,row+i);
    if (i==(mapped+1)/2)
    {
      if (i==0)
      {
        lcd.write(0);
      }
      else if (i==v_height-1)
      {
        lcd.write(5);
      }
      else
      {
        if (mapped+1==(mapped+1)/2*2) lcd.write(2);
        else lcd.write(3);
      }
    }
    else
    {
      if (i==0)
      {
        lcd.write(1);
      }
      else if (i==v_height-1)
      {
        lcd.write(4);
      }
      else
      {
        lcd.write(' ');
      }
    }
  }
}


// Class List
List::List(byte c, byte r, byte l, byte items, byte item_scr, char** list):
Hmi(c, r, l)
{
  item_rows = items;
  item_per_screen = item_scr;
  item_selected= 0;
  item_list = list;
}

List::List():
Hmi(0, 0, 0)
{
  item_rows = 0;
  item_per_screen = 0;
  item_selected= 0;
  item_list = 0;
}

void List::init(byte c, byte r, byte l, byte items, byte item_scr, char** list)
{
  col = c;
  row = r;
  length = l;
  item_rows = items;
  item_per_screen = item_scr;
  item_selected= 0;
  item_list = list;
}


void List::show()
{
  render(item_selected);  
}

void List::update(byte progr)
{
  render(progr);  
}


void List::render(byte item_sel)
{
  char indicator = '~';
  char list_buffer[22];
  byte _first_item;
  byte _last_item;
  
  item_selected = item_sel;

  _first_item=item_selected-item_per_screen/2;
  if (_first_item>127) _first_item=0;
  else if (item_selected-item_per_screen/2+item_per_screen>(item_rows - 1)) _first_item=(item_rows - 1)+1-item_per_screen;
  
  _last_item=_first_item+item_per_screen-1; // Determine last item based on first item, total item per screen, and total item.
  if (_last_item>(item_rows - 1)) _last_item=item_rows - 1;

  for (byte i=_first_item;i<_first_item+item_per_screen;i++)
  {
    if (i<=_last_item) // Copy item
    {
      byte len=strlcpy_P(list_buffer,(char*)pgm_read_word(item_list+i), length+1);
      if (len<length)
      {
        for (byte k=len;k<length;k++)
        {
          list_buffer[k]=' ';
        }	
        list_buffer[length]=0;
      }
    }
    else // Fill blank
    {
      byte j;
      for (j=0;j<length;j++)
      {
        list_buffer[j]=' ';
      }
      list_buffer[j]=0;
    }

    //Display item on LCD
    lcd.setCursor(col+((i-_first_item)/item_rows)*(length+1), row+(i-_first_item)%item_rows); 

    if (i<=_last_item)
    {
      lcd.write((i==item_selected)?indicator:' ');// Show " " or a dot
    }
    else
    {
      lcd.write(' ');
    }

    lcd.print(list_buffer);
  }
}

// Class List
ParamList::ParamList(byte c, byte r, byte l, byte items, byte item_scr, char** list, byte l_list, char** param, byte l_param, Button ** b):
Hmi(c, r, l)
{
  item_rows = items;
  item_per_screen = item_scr;
  item_selected= 0;
  item_list = list;
  length_list = l_list;
  length_param = l_param;
  item_param = param;
}

ParamList::ParamList(Button ** b):
Hmi(0, 0, 0)
{
  item_rows = 0;
  item_per_screen = 0;
  item_selected= 0;
  item_list = 0;
  length_list = 0;
  length_param = 0;
}

void ParamList::init(byte c, byte r, byte l, byte items, byte item_scr, char** list, byte l_list, char** param, byte l_param)
{
  col = c;
  row = r;
  length = l;
  item_rows = items;
  item_per_screen = item_scr;
  item_selected= 0;
  item_list = list;
  length_list = l_list;
  length_param = l_param;
  item_param = param;  
}


void ParamList::show()
{
  render(item_selected);  
}

void ParamList::update(byte progr)
{
  render(progr);  
}


void ParamList::render(byte item_sel)
{
  char indicator = '~';
  char list_buffer[22];
  byte _first_item;
  byte _last_item;
  
  item_selected = item_sel;

  _first_item=item_selected-item_per_screen/2;
  if (_first_item>127) _first_item=0;
  else if (item_selected-item_per_screen/2+item_per_screen>(item_rows - 1)) _first_item=(item_rows - 1)+1-item_per_screen;
  
  _last_item=_first_item+item_per_screen-1; // Determine last item based on first item, total item per screen, and total item.
  if (_last_item>(item_rows - 1)) _last_item=item_rows - 1;

  for (byte i=_first_item;i<_first_item+item_per_screen;i++)
  {
    if (i<=_last_item) // Copy item
    {
      byte len=strlcpy_P(list_buffer,(char*)pgm_read_word(item_list+i), length_list+1);
      if (len<length_list)
      {
        for (byte k=len;k<length_list;k++)
        {
          list_buffer[k]=' ';
        }	
        list_buffer[length]=0;
      }
      len=strlcpy(list_buffer+length_list,(char*)item_param+(6*i), length_param+1);
      if (len<length_param)
      {
        for (byte k=len;k<length_param;k++)
        {
          list_buffer[k+length_list]=' ';
        }	
        list_buffer[length]=0;
      }
    }
    else // Fill blank
    {
      byte j;
      for (j=0;j<length;j++)
      {
        list_buffer[j]=' ';
      }
      list_buffer[j]=0;
    }

    //Display item on LCD
    lcd.setCursor(col+((i-_first_item)/item_rows)*(length+1), row+(i-_first_item)%item_rows); 

    if (i<=_last_item)
    {
      lcd.write((i==item_selected)?indicator:' ');// Show " " or a dot
    }
    else
    {
      lcd.write(' ');
    }

    lcd.print(list_buffer);
  }
}


void print_welcome_screen()
{
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(P(Td5OpenComWelcome));
  lcd.setCursor(5, 1);
  lcd.print(P("by Luca72"));
  lcd.setCursor(0, 2);
  lcd.print(P("Free memory: "));
  lcd.print(freeMemory());
}

void print_connect_screen(char *str)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str);
  lcd.setCursor(0, 2);
  lcd.print(P("Connecting to ECU   "));
}

void print_instrument_screen(int rpm, float coolant_t, float turbo_p, float battery, float ambient_p, float maf, float inlet_t, float fuel_t)
{
  lcd.clear();
  print_pid(0, 0, P("RPM"), rpm, 0); 
  print_pid(10, 0, P("CoT"), coolant_t, 1);
  print_pid(0, 1, P("TbP"), turbo_p, 2); 
  print_pid(10, 1, P("BtV"), battery, 1);
  print_pid(0, 2, P("AmP"), ambient_p, 2); 
  print_pid(10, 2, P("MAF"), maf, 1);
  print_pid(0, 3, P("InT"), inlet_t, 1); 
  print_pid(10, 3, P("FuT"), fuel_t, 1);
}

void print_read_fault_codes_screen(int index, int count, char* description)
{
  char buf[7];
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(P("Read Fault C."));
  lcd.setCursor(15, 0);
  sprintf(buf, "%02d-%02d", index, count);
  lcd.print(buf);
  lcd.setCursor(0, 1);
  lcd.print(description);
}

void print_reset_fault_codes_screen(boolean yes_no)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(P("Reset Fault Codes"));
  lcd.setCursor(3, 2);
  if(yes_no)
  {
    lcd.print(P("[YES]   NO "));
  }
  else
  {
    lcd.print(P(" YES   [NO]"));
  }
}

void print_fuelling_screen(byte currentParam, boolean logActive)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  #ifdef _USE_SD_  
  if(logActive)
  {
    lcd.print(P("Fuelling (log=ON)"));    
  }
  else
  {
    lcd.print(P("Fuelling (log=OFF)"));        
  }
  #else
  lcd.print(P("Fuelling"));
  #endif
  fuellingParams.update(currentParam);
  fuellingParams.show();
}

void print_options_screen(byte currentParam)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(P("Options"));
  optionsParams.update(currentParam);
  optionsParams.show();
}

void update_fuelling_screen(byte currentParam)
{
  fuellingParams.update(currentParam);
}


void print_pid(byte col, byte row, char* tag, float fvalue, byte precision)
{
  lcd.setCursor(col, row);
  lcd.print(tag);
  byte colOffset;
  if(precision == 0)
  {
    colOffset = 5;
  }
  else
  {
    colOffset = 5 - precision;
  }
  lcd.setCursor(col + colOffset, row);
  if (fvalue < 10.0)
    lcd.print(' ');
  if (fvalue < 100.0)
    lcd.print(' ');
  if ((fvalue < 1000.0) && (precision == 0))
    lcd.print(' ');
  lcd.print(fvalue, precision);
}

void setBrightness(byte bright)
{
  brightness = bright;   
}

void incBrightness(byte inc)
{
  brightness += inc;   
}

void decBrightness(byte inc)
{
  brightness += inc;   
}

