/*
  OLED_StatusIcons.cpp - Add-on library to have a statusbar with icons for OLED_I2C
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library is an add-on to OLED_I2C and will not work on its own.

  This library will allow you to display an interrupt-driven status bar with 
  icons on the display. The status bar can be positioned either at the top or 
  the bottom of the display, and the icons can be left or right aligned. The 
  library supports 8x8 and 16x16 pixels icons but you cannot mix the two 
  sizes. Only one size can be used at a time.

  You can always find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#include "OLED_StatusIcons.h"
#include "icons8.c"
#include "icons16.c"

#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#include "hardware/avr/HW_AVR.h"
#elif defined(__PIC32MX__)
	#include "hardware/pic32/HW_PIC32.h"
#elif defined(__arm__)
	#include "hardware/arm/HW_ARM.h"
#endif

OLED_StatusIcons::OLED_StatusIcons(OLED *ptrOLED, uint8_t size, uint8_t position)
{
	_OLED		= ptrOLED;
	_size		= size;
	_position	= position;
	if (size == ICONSIZE_8X8)
		_max_icon = 13;
	else if (size == ICONSIZE_16X16)
		_max_icon = 6;
}

void OLED_StatusIcons::begin()
{
	_running = false;
	_int_speed = 1000;
	for (int i = 0; i < _max_icon; i++)
	{
		_icons[i].bitmap = 0;
		_icons[i].enabled = false;
	}
}

void OLED_StatusIcons::updateSpeed(uint16_t ms)
{
	if ((ms >= 100) and (ms <= 10000))
	{
		_int_speed = ms;
		_int_counter = ms - 1;
	}
}

void OLED_StatusIcons::enableStatusbar()
{
	_int_counter = _int_speed-1;
	__start_interrupt();
	_running = true;
}

void OLED_StatusIcons::disableStatusbar()
{
	__stop_interrupt();
	_running = false;
}

void OLED_StatusIcons::refreshStatusbar()
{
	if (_running == true)
		_int_counter = _int_speed - 1;
}

boolean OLED_StatusIcons::createIcon(byte position, uint8_t* bitmap, boolean enabled)
{
	if ((_icons[position].bitmap == 0) and (position <= _max_icon))
	{
		_icons[position].bitmap = bitmap;
		_icons[position].enabled = enabled;
		return true;
	}
	else
		return false;
}

boolean OLED_StatusIcons::deleteIcon(byte position)
{
	if (_icons[position].bitmap != 0)
	{
		_icons[position].bitmap = 0;
		_icons[position].enabled = false;
		return true;
	}
	else
		return false;
}

void OLED_StatusIcons::enableIcon(byte position)
{
	if (_icons[position].bitmap != 0)
		_icons[position].enabled = true;

}

void OLED_StatusIcons::disableIcon(byte position)
{
	if (_icons[position].bitmap != 0)
		_icons[position].enabled = false;
}

void OLED_StatusIcons::changeIcon(byte position, uint8_t* bitmap)
{
	if (_icons[position].bitmap != 0)
		_icons[position].bitmap = bitmap;
}
