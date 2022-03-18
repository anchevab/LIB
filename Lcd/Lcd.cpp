/*
 * Copyright 2008 Josh Kropf
 * 
 * This file is part of the Arduino LCD Library.
 * 
 * Arduino LCD Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Arduino LCD Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Lemon Launcher; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "Lcd.h"

extern "C" {
   #include <inttypes.h>
   #include "WConstants.h"
   //#include "WProgram.h"
}

/* extract 4 bit value from the mask at the given offset */
#define PIN(mask,off) (mask>>off)&0xf

/* List of available commands */
#define CMD_CLEAR      0x01
#define CMD_HOME       0x02
#define CMD_ENTRY_MODE 0x04
#define CMD_DISPLAY    0x08
#define CMD_SHIFT      0x10
#define CMD_FUNCTION   0x20
#define CMD_CGRAM_ADR  0x40
#define CMD_DGRAM_ADR  0x80

#define REG_INST 0x00 // write instruction
#define REG_DATA 0x10 // write data into ram
#define REG_READ 0x01 // read busy flag/address counter

void
Lcd::select_reg(uint8_t reg)
{
   digitalWrite(PIN(_ctrl_pins, 8), (reg&0xf0)>>4);
   digitalWrite(PIN(_ctrl_pins, 4),  reg&0x0f);
}

void
Lcd::send(uint8_t reg, uint8_t data)
{
   // when RW bin is not connected, comment out busy flag check
   // and use fixed delay (might need to adjust delay length)
   // delay(5);
   check_bf();
   
   select_reg(reg);
   
   if (_is4bit) {
      // in 4 pin mode, send upper 4 bits then lower 4 bits
      send_4bits(data >> 4);
      send_4bits(data & 0xf);
   } else {
      send_8bits(data);
   }
}

void
Lcd::send_4bits(uint8_t data)
{
   // 4 pin mode we use only the upper 16 bits (4bits x 4 pins)
   uint32_t pins = _data_pins;
   
   for (int i=0; i<4; i++) {
      digitalWrite(pins & 0xf, data & 1);
      pins >>= 4;
      data >>= 1;
   }
   
   pulse_enable();
}

void
Lcd::send_8bits(uint8_t data)
{
   uint32_t pins = _data_pins;
   
   for (int i=0; i<8; i++) {
      digitalWrite(pins & 0xf, data & 1);
      pins >>= 4;
      data >>= 1;
   }
   
   pulse_enable();
}

void
Lcd::set_enable(uint8_t val)
{
   digitalWrite(PIN(_ctrl_pins,0), val);
   delayMicroseconds(1);
}

void
Lcd::pulse_enable()
{
   digitalWrite(PIN(_ctrl_pins,0), HIGH);
   delayMicroseconds(1);
   digitalWrite(PIN(_ctrl_pins,0), LOW);
   delayMicroseconds(1);
}

void
Lcd::check_bf()
{
   // busy flag (D7 pin) is at offset 12 for 4bit and 28 for 8bit
   uint8_t bf_pin = PIN(_data_pins, (_is4bit? 12 : 28));
   
   pinMode(bf_pin, INPUT); // put D7 into input mode
   select_reg(REG_READ);   // select register for reading busy flag

   uint8_t bf;
   do {
      set_enable(HIGH);
      bf = digitalRead(bf_pin);
      set_enable(LOW);
      
      // this operation has two steps in 4bit bus mode
      // 1) get the busy flag bit and 3 bits of address counter
      // 2) remaining 4 bits of address counter
      // so do one more pulse of the enable pin to finish the op
      if (_is4bit)
         pulse_enable();
   } while (bf);
   
   pinMode(bf_pin, OUTPUT); // return D7 to output mode
}

Lcd::Lcd(uint8_t width, uint8_t func) : _cols(width), _function(func)
{
   _is4bit = !(_function & FUNCTION_8BIT);
   
   // set default pin masks
   _ctrl_pins = CTRLPINS(1,2,3);
   _data_pins = _8PINS(4,5,6,7,8,9,10,11);
}

void
Lcd::setup()
{
   uint16_t cpins = _ctrl_pins;
   uint32_t dpins = _data_pins;
   
   // setup control pins
   for (int i=0; i<3; i++) {
      pinMode(cpins&0xf, OUTPUT);
      cpins >>=4;
   }
   
   // setup data pins
   for (int i=0; i<(_is4bit? 4 : 8); i++) {
      pinMode(dpins&0xf, OUTPUT);
      dpins >>=4;
   }
   
   // spec says wait for the internal reset circuit to finish
   // before trying to do initialization by instruction
   delay(50);
   
   select_reg(REG_INST);  // use instruction register
   
   if (_is4bit) {
      send_4bits(0x03);  // function set 8bit wait 5 millis
      delay(5);

      send_4bits(0x03);  // function set 8bit wait 100 micros
      delayMicroseconds(150);

      send_4bits(0x03);  // final 8bit function set wait 100 micros
      delayMicroseconds(150);
      
      send_4bits(0x02);  // first 4bit function command, now bf can be checked
   } else {
      send_8bits(0x30);
      delay(5);

      send_8bits(0x30);
      delayMicroseconds(150);

      send_8bits(0x30);
   }
   
   // send final funtion command, can't be set again after this
   send(REG_INST, CMD_FUNCTION | _function);
   
   // remaining three instructions of the initialization routine
   // hd44780 spec states the second cmd should be display clear
   // but display on is the only one that works
   display(DISPLAY_OFF);
   display(DISPLAY_ON);
   entry_mode(ENTRY_CURSOR_INC | ENTRY_NOSHIFT);
}

void
Lcd::entry_mode(uint8_t entry)
{
   send(REG_INST, CMD_ENTRY_MODE | entry);
}

void
Lcd::display(uint8_t display)
{
   send(REG_INST, CMD_DISPLAY | display);
}

void
Lcd::shift(uint8_t shift)
{
   send(REG_INST, CMD_SHIFT | shift);
}

void
Lcd::clear()
{
   send(REG_INST, CMD_CLEAR);
}

void
Lcd::home()
{
   send(REG_INST, CMD_HOME);
}

void
Lcd::move_to(int col, int row)
{
   if (_function & FUNCTION_2LINE) {
      switch(row) {
         case 1:
            send(REG_INST, CMD_DGRAM_ADR | col-1); break;
         case 3:
            send(REG_INST, CMD_DGRAM_ADR | _cols+col-1); break;
         case 2:
            send(REG_INST, CMD_DGRAM_ADR | 0x40+col-1); break;
         case 4:
            send(REG_INST, CMD_DGRAM_ADR | 0x40+_cols+col-1 ); break;
      }
   } else {
      send(REG_INST, CMD_DGRAM_ADR | ((row-1)*_cols)+col-1);
   }
}

void
Lcd::print(char c)
{
   send(REG_DATA, c);
}

void
Lcd::print(char* s)
{
   while(*s != 0x00) {
      print(*s);
      s++;
   }
}

void
Lcd::print(unsigned long n, uint8_t base)
{
   char buf[8 * sizeof(long)];
   int i = 0;

   if (n == 0) {
      print('0');
      return;
   }

   while (n > 0) {
      buf[i++] = n % base;
      n /= base;
   }

   for(; i > 0; i--) {
      print((char) (buf[i - 1] < 10?
               '0' + buf[i - 1] :
               'A' + buf[i - 1] - 10));
   }
}

void
Lcd::print(long n, uint8_t base)
{
   if (n < 0) {
      print('-');
      n = -n;
   }

   print((unsigned long)n);
}

void
Lcd::define_char(uint8_t index, uint8_t data[])
{
   int h = _function & FUNCTION_5x11? 11 : 8;
   for (int i=0; i<h; i++) {
      send(REG_INST, CMD_CGRAM_ADR | (index*h)+i);
      send(REG_DATA, data[i]);
   }
}
