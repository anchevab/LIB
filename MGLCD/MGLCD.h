/*
  MGLCD.h - Arduino/chipKit library support for Monochrome Graphics LCDs
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  Basic functionality of this library is based on the demo-code provided by
  ElecFreaks.

  This library has been made to make it easy to use Monochrome Graphics LCDs
  with an Arduino.

  You can find the latest version of the library at 
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

#ifndef MGLCD_h
#define MGLCD_h

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

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

struct _current_font
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
	uint8_t inverted;
};

class MGLCD
{
	public:
		MGLCD(uint8_t _D0, uint8_t _D1, uint8_t _D2, uint8_t _D3, uint8_t _D4, uint8_t _D5, uint8_t _D6, uint8_t _D7, uint8_t _A0, uint8_t _RW, uint8_t _EP, uint8_t _RST);

		void	initLCD();
		void	rotateDisplay(uint8_t value);
		void	clrScr();
		void	fillScr();
		void	invert(bool mode);
		void	setPixel(uint8_t x, uint8_t y);
		void	clrPixel(uint8_t x, uint8_t y);
		void	invPixel(uint8_t x, uint8_t y);
		void	drawLine(int x1, int y1, int x2, int y2);
		void	drawRect(int x1, int y1, int x2, int y2);
		void	drawRoundRect(int x1, int y1, int x2, int y2);
		void	drawCircle(int x, int y, int radius);
		void	drawBitmap(int x, int y, bitmapdatatype bitmap, int sx, int sy);
		void	invertText(bool mode);
		void	print(char *st, int x, int y);
		void	print(String st, int x, int y);
		void	printNumI(long num, int x, int y, int length=0, char filler=' ');
		void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ');
		void	setFont(uint8_t* font);

	protected:
		regtype					*P_A0, *P_RW, *P_EP, *P_RST;
		regsize					B_A0, B_RW, B_EP, B_RST;
		regtype					*PO_DB[8];
		regtype					*PI_DB[8];
		regtype					*DD_DB[8];
		regsize					B_DB[8];
		uint8_t					DDR[8];
		volatile uint8_t		_flip_horiz;
		volatile uint8_t		_inited;
		_current_font	cfont;

		void	_send_com(uint8_t data);
		void	_send_data(uint8_t data);
		uint8_t	_read_data(uint8_t dummy=false);
		void	_data_direction(uint8_t dir);
		void	_get_DDR_pins(uint8_t _D0, uint8_t _D1, uint8_t _D2, uint8_t _D3, uint8_t _D4, uint8_t _D5, uint8_t _D6, uint8_t _D7);
		void	setpage(uint8_t page);
		void	setaddr(uint8_t addr);
		void	drawHLine(int x, int y, int l);
		void	drawVLine(int x, int y, int l);
		void	_print_char(unsigned char c, int x, int row);
		void	_convert_float(char *buf, double num, int width, byte prec);
};

#endif