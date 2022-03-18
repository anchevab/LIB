/*
  MGLCD.cpp - Arduino/chipKit library support for Monochrome Graphics LCDs
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

#include "MGLCD.h"
//#include <pins_arduino.h>
#if defined(__AVR__)
	#include "hardware/avr/HW_AVR.h"
#elif defined(__PIC32MX__)
	#pragma message("Compiling for PIC32 Architecture...")
	#include "hardware/pic32/HW_PIC32.h"
#elif defined(__arm__)
	#pragma message("Compiling for ARM Architecture...")
	#include "hardware/arm/HW_ARM.h"
#endif


/****************************************************************************************/
/* Public                                                                               */
/****************************************************************************************/

MGLCD::MGLCD(uint8_t _D0, uint8_t _D1, uint8_t _D2, uint8_t _D3, uint8_t _D4, uint8_t _D5, uint8_t _D6, uint8_t _D7, uint8_t _A0, uint8_t _RW, uint8_t _EP, uint8_t _RST)
{
	P_A0	= portOutputRegister(digitalPinToPort(_A0));
	B_A0	= digitalPinToBitMask(_A0);
	P_RW	= portOutputRegister(digitalPinToPort(_RW));
	B_RW	= digitalPinToBitMask(_RW);
	P_EP	= portOutputRegister(digitalPinToPort(_EP));
	B_EP	= digitalPinToBitMask(_EP);
	P_RST	= portOutputRegister(digitalPinToPort(_RST));
	B_RST	= digitalPinToBitMask(_RST);

	PO_DB[0]	= portOutputRegister(digitalPinToPort(_D0));
	PO_DB[1]	= portOutputRegister(digitalPinToPort(_D1));
	PO_DB[2]	= portOutputRegister(digitalPinToPort(_D2));
	PO_DB[3]	= portOutputRegister(digitalPinToPort(_D3));
	PO_DB[4]	= portOutputRegister(digitalPinToPort(_D4));
	PO_DB[5]	= portOutputRegister(digitalPinToPort(_D5));
	PO_DB[6]	= portOutputRegister(digitalPinToPort(_D6));
	PO_DB[7]	= portOutputRegister(digitalPinToPort(_D7));

	PI_DB[0]	= portInputRegister(digitalPinToPort(_D0));
	PI_DB[1]	= portInputRegister(digitalPinToPort(_D1));
	PI_DB[2]	= portInputRegister(digitalPinToPort(_D2));
	PI_DB[3]	= portInputRegister(digitalPinToPort(_D3));
	PI_DB[4]	= portInputRegister(digitalPinToPort(_D4));
	PI_DB[5]	= portInputRegister(digitalPinToPort(_D5));
	PI_DB[6]	= portInputRegister(digitalPinToPort(_D6));
	PI_DB[7]	= portInputRegister(digitalPinToPort(_D7));

	_get_DDR_pins(_D0, _D1, _D2, _D3, _D4, _D5, _D6, _D7);

	B_DB[0]		= digitalPinToBitMask(_D0);
	B_DB[1]		= digitalPinToBitMask(_D1);
	B_DB[2]		= digitalPinToBitMask(_D2);
	B_DB[3]		= digitalPinToBitMask(_D3);
	B_DB[4]		= digitalPinToBitMask(_D4);
	B_DB[5]		= digitalPinToBitMask(_D5);
	B_DB[6]		= digitalPinToBitMask(_D6);
	B_DB[7]		= digitalPinToBitMask(_D7);

	pinMode(_RST, OUTPUT);
	digitalWrite(_RST, LOW);
	pinMode(_A0,  OUTPUT);
	pinMode(_RW,  OUTPUT);
	pinMode(_EP,  OUTPUT);

	_flip_horiz=0;
	_inited=0;
}

void	MGLCD::initLCD()
{
	cbi(P_RST, B_RST);
	cbi(P_EP,  B_EP);
	delay(50);
	sbi(P_RST, B_RST);

	_send_com(0xaf);		// ( 1) Display ON	
	_send_com(0xa3);		// (11) LCD Bias Set: 1/7
	if (_flip_horiz==1)
	{
		_send_com(0xa1);	// ( 8) ADC select: Reverse
		_send_com(0xc0);	// (15) Common output mode select: Normal
	}
	else
	{
		_send_com(0xa0);	// ( 8) ADC select: normal
		_send_com(0xc8);	// (15) Common output mode select: Reverse
	}
	_send_com(0x27);		// (17) V5 voltage regulator internal resistor ratio set: 111
	_send_com(0x81);		// (18) Electronic volume mode set
	_send_com(0x24);		//      Electronic volume register set: 100100
	_send_com(0x2f);		// (16) Power Control Set: 111

	_send_com(0xa4);		// (10) Display all points: OFF
	_send_com(0xa6);		// ( 9) Display normal/reverse: NORMAL
	_send_com(0xac);		// (19) Static indicator: OFF
	_send_com(0x40);		// ( 2) Display start line set: 000000
	_inited=1;

	clrScr();
}

void	MGLCD::rotateDisplay(uint8_t value)
{
	if (_inited==0)
	{
		if (value==true)
			_flip_horiz=1;
		else
			_flip_horiz=0;
	}
}

void	MGLCD::clrScr()
{
	int page,addr;

	for(page=0; page<8; page++)
	{
		setpage(page);
		setaddr(0);
		for(addr=0; addr<128; addr++)
		{
			_send_data(0);
		}
	}
}

void	MGLCD::fillScr()
{
	int page,addr;

	for(page=0; page<8; page++)
	{
		setpage(page);
		setaddr(0);
		for(addr=0; addr<128; addr++)
		{
			_send_data(0xff);
		}
	}
}

void	MGLCD::invert(bool mode)
{
	if (mode==true)
		_send_com(0xa7);
	else
		_send_com(0xa6);
}

void	MGLCD::setPixel(uint8_t x, uint8_t y)
{
	uint8_t page, bit, data;

	page = y / 8;
	bit  = y % 8;

	setpage(page);
	setaddr(x);

	_send_com(0xe0);
	data=_read_data(true); // Dummy read
	data=_read_data();
	data |= (1<<bit);
	_send_data(data);
	_send_com(0xee);
}

void	MGLCD::clrPixel(uint8_t x, uint8_t y)
{
	uint8_t page, bit, data;

	page = y / 8;
	bit  = y % 8;

	setpage(page);
	setaddr(x);

	_send_com(0xe0);
	data=_read_data(true); // Dummy read
	data=_read_data();
	data &= ~(1<<bit);
	_send_data(data);
	_send_com(0xee);
}

void	MGLCD::invPixel(uint8_t x, uint8_t y)
{
	uint8_t page, bit, data;

	page = y / 8;
	bit  = y % 8;

	setpage(page);
	setaddr(x);

	_send_com(0xe0);
	data=_read_data(true); // Dummy read
	data=_read_data();
	data ^= (1<<bit);
	_send_data(data);
	_send_com(0xee);
}

void	MGLCD::drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=(double(y2-y1)/double(x2-x1));
		ty=double(y1);
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				setPixel(i, int(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				setPixel(i, int(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=(float(x2-x1)/float(y2-y1));
		tx=float(x1);
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		setPixel(int(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		setPixel(int(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void	MGLCD::drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1+1);
}

void	MGLCD::drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		setPixel(x1+1,y1+1);
		setPixel(x2-1,y1+1);
		setPixel(x1+1,y2-1);
		setPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-3);
		drawHLine(x1+2, y2, x2-x1-3);
		drawVLine(x1, y1+2, y2-y1-3);
		drawVLine(x2, y1+2, y2-y1-3);
	}
}

void	MGLCD::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	setPixel(x, y + radius);
	setPixel(x, y - radius);
	setPixel(x + radius, y);
	setPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setPixel(x + x1, y + y1);
		setPixel(x - x1, y + y1);
		setPixel(x + x1, y - y1);
		setPixel(x - x1, y - y1);
		setPixel(x + y1, y + x1);
		setPixel(x - y1, y + x1);
		setPixel(x + y1, y - x1);
		setPixel(x - y1, y - x1);
	}
}

void	MGLCD::drawBitmap(int x, int y, bitmapdatatype bitmap, int sx, int sy)
{
	uint8_t page, bit, data, data2, ry, crow, mask, xoffset;

	if (x<0)
	{
		xoffset=abs(x);
		x=0;
	}
	else
		xoffset=0;

	if ((y % 8)==0)
	{
		crow=0;
		ry=sy;
		page = y / 8;
		while (ry>=8)
		{
			if (page<8)
			{
				setpage(page);
				setaddr(x);
				for(int cx=xoffset; cx<sx; cx++)
				{
					data=bitmapbyte(cx+(crow*sx));

					_send_data(data);
				}
			}
			ry-=8;
			page++;
			crow++;
		}
		if (ry!=0)
		{
			if (page<128)
			{
				mask=(1<<ry)-1;
				setpage(page);
				setaddr(x);
				_send_com(0xe0);
				for(int cx=xoffset; cx<sx; cx++)
				{
					data=bitmapbyte(cx+(crow*sx));

					data2=_read_data(true); // Dummy read
					data2=_read_data();
					data=(data & mask) | (data2 & ~mask); 
					_send_data(data);
				}
				_send_com(0xee);
			}
		}
	}
	else
	{
		if (sy<=8)
		{
			if (y<0)
			{
				page = (y / 8)-1;
				bit  = 8-abs(y % 8);

			}
			else
			{
				page = y / 8;
				bit  = y % 8;
			}
			if ((bit + sy)<=8)
			{
				if (page<8)
				{
					mask = ((1<<sy)-1)<<bit;
					setpage(page);
					setaddr(x);
					_send_com(0xe0);
					for(int cx=xoffset; cx<sx; cx++)
					{
						data=bitmapbyte(cx);

						data2=_read_data(true); // Dummy read
						data2=_read_data();
						data=((data<<bit) & mask) | (data2 & ~mask); 
						_send_data(data);
					}
					_send_com(0xee);
				}
			}
			else
			{
				ry = sy;
				mask = 0xff-((1<<bit)-1);
				if (page<8)
				{
					setpage(page);
					setaddr(x);
					_send_com(0xe0);
					for(int cx=xoffset; cx<sx; cx++)
					{
						data=bitmapbyte(cx);

						data2=_read_data(true); // Dummy read
						data2=_read_data();
						data=((data<<bit) & mask) | (data2 & ~mask); 
						_send_data(data);
					}
					_send_com(0xee);
				}
				page++;
				ry = ry-(8-bit);
				mask=(1<<ry)-1;
				if (page<8)
				{
					setpage(page);
					setaddr(x);
					_send_com(0xe0);
					for(int cx=xoffset; cx<sx; cx++)
					{
						data=bitmapbyte(cx);

						data=(data>>(8-bit)); 

						data2=_read_data(true); // Dummy read
						data2=_read_data();
						data=(data & mask) | (data2 & ~mask); 
						_send_data(data);
					}
					_send_com(0xee);
				}
			}
		}
		else
		{
			ry   = sy;
			crow = 0;
			if (y<0)
			{
				page = (y / 8)-1;
				bit  = 8-abs(y % 8);

			}
			else
			{
				page = y / 8;
				bit  = y % 8;
			}
			mask = 0xff-((1<<bit)-1);
			if (page<8)
			{
				setpage(page);
				setaddr(x);
				_send_com(0xe0);
				for(int cx=xoffset; cx<sx; cx++)
				{
					data=bitmapbyte(cx+(crow*sx));

					data2=_read_data(true); // Dummy read
					data2=_read_data();
					data=((data<<bit) & mask) | (data2 & ~mask); 
					_send_data(data);
				}
				_send_com(0xee);
			}
			page++;
			ry = ry-(8-bit);

			while (ry>7)
			{
				if (page<8)
				{
					setpage(page);
					setaddr(x);
					for(int cx=xoffset; cx<sx; cx++)
					{
						data=bitmapbyte(cx+(crow*sx));
						data2=bitmapbyte(cx+((crow+1)*sx));

						data=(data>>(8-bit)) | (data2<<bit); 
						_send_data(data);
					}
				}
				ry-=8;
				page++;
				crow++;
			}

			if (ry>0)
			{
				mask=(1<<ry)-1;
				if (page<8)
				{
					setpage(page);
					setaddr(x);
					_send_com(0xe0);
					for(int cx=xoffset; cx<sx; cx++)
					{
						data=bitmapbyte(cx+(crow*sx));
						data2=bitmapbyte(cx+((crow+1)*sx));

						data=(data>>(8-bit)) | (data2<<bit); 

						data2=_read_data(true); // Dummy read
						data2=_read_data();
						data=(data & mask) | (data2 & ~mask); 
						_send_data(data);
					}
					_send_com(0xee);
				}
			}
		}
	}
}

void	MGLCD::invertText(bool mode)
{
	if (mode==true)
		cfont.inverted=1;
	else
		cfont.inverted=0;
}

void	MGLCD::print(char *st, int x, int y)
{
	unsigned char ch;
	int stl;

	stl = strlen(st);
	if (x == RIGHT)
		x = 128-(stl*cfont.x_size);
	if (x == CENTER)
		x = (128-(stl*cfont.x_size))/2;

	for (int cnt=0; cnt<stl; cnt++)
			_print_char(*st++, x + (cnt*(cfont.x_size)), y);
}

void	MGLCD::print(String st, int x, int y)
{
	char buf[st.length()+1];

	st.toCharArray(buf, st.length()+1);
	print(buf, x, y);
}

void	MGLCD::printNumI(long num, int x, int y, int length, char filler)
{
	char buf[25];
	char st[27];
	boolean neg=false;
	int c=0, f=0;
  
	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}
	  
		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;
	  
		if (neg)
		{
			st[0]=45;
		}
	  
		if (length>(c+neg))
		{
			for (int i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		for (int i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;
	}

	print(st,x,y);
}

void	MGLCD::printNumF(double num, byte dec, int x, int y, char divider, int length, char filler)
{
	char st[27];
	boolean neg=false;

	if (dec<1)
		dec=1;
	else if (dec>5)
		dec=5;

	if (num<0)
		neg = true;

	_convert_float(st, num, length, dec);

	if (divider != '.')
	{
		for (int i=0; i<sizeof(st); i++)
			if (st[i]=='.')
				st[i]=divider;
	}

	if (filler != ' ')
	{
		if (neg)
		{
			st[0]='-';
			for (int i=1; i<sizeof(st); i++)
				if ((st[i]==' ') || (st[i]=='-'))
					st[i]=filler;
		}
		else
		{
			for (int i=0; i<sizeof(st); i++)
				if (st[i]==' ')
					st[i]=filler;
		}
	}

	print(st,x,y);
}

void	MGLCD::setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
	cfont.inverted=0;
}



/****************************************************************************************/
/* Proctected                                                                           */
/****************************************************************************************/

void	MGLCD::_send_com(uint8_t data)
{
	_data_direction(OUTPUT);
	cbi(P_A0, B_A0);
	cbi(P_RW, B_RW);

	for (int i=0; i<8; i++)
	{
		if (data & 1)
			sbi(PO_DB[i], B_DB[i]);
		else
			cbi(PO_DB[i], B_DB[i]);
		data=data>>1;
	}

	pulseLatch;
}

void	MGLCD::_send_data(uint8_t data)
{  
	_data_direction(OUTPUT);
	sbi(P_A0, B_A0);
	cbi(P_RW, B_RW);

	for (int i=0; i<8; i++)
	{
		if (data & 1)
			sbi(PO_DB[i], B_DB[i]);
		else
			cbi(PO_DB[i], B_DB[i]);
		data=data>>1;
	}

	pulseLatch;
}

uint8_t	MGLCD::_read_data(uint8_t dummy)
{  
	uint8_t data = 0;

	_data_direction(INPUT);
	sbi(P_A0, B_A0);
	sbi(P_RW, B_RW);
	sbi(P_EP, B_EP);

	if (!dummy)
		for (int i=7; i>=0; i--)
		{
			data=data<<1;
			if ((*PI_DB[i] & B_DB[i])>0)
				data++;
		}
	cbi(P_EP, B_EP);
	return data;
}

void	MGLCD::setpage(uint8_t page)
{
	page |= 0xb0;
	_send_com(page);
}

void	MGLCD::setaddr(uint8_t addr)
{
	uint8_t data_hi, data_low;
	if (_flip_horiz==1)
		addr+=4;
	data_hi = (addr>>4) | 0x10;
	data_low= (addr & 0x0f);
	_send_com(data_hi);
	_send_com(data_low);
}

void	MGLCD::drawHLine(int x, int y, int l)
{
	uint8_t page, bit, data;

	if ((x>=0) and (x<128) and (y>=0) and (y<64))
	{
		page = y / 8;
		bit  = y % 8;

		setpage(page);
		setaddr(x);

		_send_com(0xe0);
		for (int cx=0; cx<l; cx++)
		{
			data=_read_data(true); // Dummy read
			data=_read_data();
			data |= (1<<bit);
			_send_data(data);
		}
		_send_com(0xee);
	}
}

void	MGLCD::drawVLine(int x, int y, int l)
{
	int page, bit, ry, data, mask;

	if ((x>=0) and (x<128) and (y>=0) and (y<64))
	{
		ry   = l;
		page = y / 8;
		bit  = y % 8;
		
		if ((bit!=0) and ((bit+ry)<8))
		{
			mask = ((1<<ry)-1)<<bit;
			setpage(page);
			setaddr(x);
			_send_com(0xe0);
			data=_read_data(true); // Dummy read
			data=_read_data();
			data = (data & ~mask) | mask;
			_send_data(data);
			_send_com(0xee);
		}
		else
		{
			if (bit!=0)
			{
				setpage(page);
				setaddr(x);
				_send_com(0xe0);
				data=_read_data(true); // Dummy read
				data=_read_data();
				data = (~((1<<bit)-1)) | (data & ((1<<bit)-1));
				_send_data(data);
				_send_com(0xee);
				page++;
				ry -= (8-bit);
			}

			while ((ry>7) and (page<8))
			{
				setpage(page);
				setaddr(x);
				_send_data(0xff);
				page++;
				ry-=8;
			}

			if ((ry!=0) and (page<8))
			{
				setpage(page);
				setaddr(x);
				_send_com(0xe0);
				data=_read_data(true); // Dummy read
				data=_read_data();
				data = ((1<<ry)-1) | (data & (~((1<<ry)-1)));
				_send_data(data);
				_send_com(0xee);
			}
		}
	}
}

void	MGLCD::_print_char(unsigned char c, int x, int y)				// Need optimize
{
	uint16_t page, bit, data, data2, ry, crow, mask, font_idx;

	if ((y>=0) and ((y+cfont.y_size)<128))
	{
		page = y / 8;
		bit  = y % 8;

		ry   = cfont.y_size;
		crow = 0;
		mask = 0xff-((1<<bit)-1);
		font_idx = ((c - cfont.offset)*(cfont.x_size*(cfont.y_size/8)))+4;
		if (bit!=0)
		{
			setpage(page);
			setaddr(x);
			_send_com(0xe0);
			for(int cx=0; cx<cfont.x_size; cx++)
			{
				data=fontbyte(font_idx+cx+(crow*cfont.x_size));
				if (cfont.inverted)
					data = ~data;

				data2=_read_data(true); // Dummy read
				data2=_read_data();
				data=((data<<bit) & mask) | (data2 & ~mask); 
				_send_data(data);
			}
			_send_com(0xee);
			page++;
			ry = ry-(8-bit);
		}

		while (ry>7)
		{
			setpage(page);
			setaddr(x);
			for(int cx=0; cx<cfont.x_size; cx++)
			{
				data=fontbyte(font_idx+cx+(crow*cfont.x_size));
				if (bit!=0)
				{
					data2=fontbyte(font_idx+cx+((crow+1)*cfont.x_size));
					data=(data>>(8-bit)) | (data2<<bit); 
				}
				if (cfont.inverted)
					data = ~data;
				_send_data(data);
			}
			ry-=8;
			page++;
			crow++;
		}

		if (ry>0)
		{
			mask=(1<<ry)-1;
			setpage(page);
			setaddr(x);
			_send_com(0xe0);
			for(int cx=0; cx<cfont.x_size; cx++)
			{
				data=fontbyte(font_idx+cx+(crow*cfont.x_size));
				if (bit!=0)
				{
					data2=fontbyte(font_idx+cx+((crow+1)*cfont.x_size));
					data=(data>>(8-bit)) | (data2<<bit); 
				}
				if (cfont.inverted)
					data = ~data;

				data2=_read_data(true); // Dummy read
				data2=_read_data();
				data=(data & mask) | (data2 & ~mask); 
				_send_data(data);
			}
			_send_com(0xee);
		}
	}
}

