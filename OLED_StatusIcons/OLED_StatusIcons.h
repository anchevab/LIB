/*
  OLED_StatusIcons.h - Add-on library to have a statusbar with icons for OLED_I2C
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

#ifndef OLED_StatusIcons_h
#define OLED_StatusIcons_h

#include "OLED_I2C.h"

#if defined(__AVR__)
	#include "Arduino.h"
	#include "hardware/avr/HW_AVR_defines.h"
#elif defined(__PIC32MX__)
	#include "WProgram.h"
	#include "hardware/pic32/HW_PIC32_defines.h"
#elif defined(__arm__)
	#include "Arduino.h"
	#include "hardware/arm/HW_ARM_defines.h"
#endif

#define ICONSIZE_8X8				1
#define ICONSIZE_16X16				2

#define ICONPOSITION_TOP_RIGHT		0
#define ICONPOSITION_TOP_LEFT		1
#define ICONPOSITION_BOTTOM_RIGHT	2
#define ICONPOSITION_BOTTOM_LEFT	3

#define NUMBER_OF_ICONS				14

struct _icon
{
	uint8_t*	bitmap;
	boolean		enabled;
};

static	OLED			*_OLED;
static	uint8_t			_size;
static	uint8_t			_position;
static	uint16_t		_int_counter;
static	uint16_t		_int_speed;
static	_icon			_icons[NUMBER_OF_ICONS];
static	uint8_t			_max_icon;

class OLED_StatusIcons
{
	public:
		OLED_StatusIcons(OLED *ptrOLED, uint8_t size, uint8_t position);

		void	begin();
		void	updateSpeed(uint16_t ms);
		void	enableStatusbar();
		void	disableStatusbar();
		void	refreshStatusbar();
		boolean	createIcon(byte position, uint8_t* bitmap, boolean enabled = false);
		boolean	deleteIcon(byte position);
		void	enableIcon(byte position);
		void	disableIcon(byte position);
		void	changeIcon(byte position, uint8_t* bitmap);

protected:
		boolean		_running;

		void	__start_interrupt();
		void	__stop_interrupt();
};

#endif