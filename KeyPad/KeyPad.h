/*
  KeyPad.h - Arduino and chipKit library support for KeyPads
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is just a quick and easy way to get input through keypads. The 
  library supports keypads with up to 6 columns and up to 5 rows of keys.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#ifndef keypad_h
#define keypad_h

#if defined(__AVR__)
  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)
	#include "Arduino.h"
  #else
    #error "Unsupported AVR MCU!"
  #endif  
#elif defined(__PIC32MX__)
  #if defined(__32MX320F128H__) || defined(__32MX795F512L__)
	#include "Wprogram.h"
  #else
    #error "Unsupported PIC32 MCU!"
  #endif  
#elif defined(__arm__)
  #if defined(__SAM3X8E__)
	#include "Arduino.h"
  #else
    #error "Unsupported ARM MCU!"
  #endif  
#else
  #error "Unsupported MCU architecture!"
#endif

#define MAX_ROWS	5
#define MAX_COLS	6

class KeyPad
{ 
public:
	KeyPad(int cols, int rows);

	void	setColPins(int c0, int c1 = -1, int c2 = -1, int c3 = -1, int c4 = -1, int c5 = -1);
	void	setRowPins(int r0, int r1 = -1, int r2 = -1, int r3 = -1, int r4 = -1);
	void	setKeyChars(int r, char *chars);
	void	setDebounceDelay(int d);
	char	readKeys();
	int		readRaw();

private:
	int		_num_cols, _num_rows;
	int		_pinCol[MAX_COLS], _pinRow[MAX_ROWS];
	char	_chars[MAX_COLS][MAX_ROWS];
	int		_delay;
};


#endif