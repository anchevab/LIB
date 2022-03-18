/*
  KeyPad.cpp - Arduino and chipKit library support for KeyPads
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

#include "KeyPad.h"

KeyPad::KeyPad(int cols, int rows)
{
	if (cols <= MAX_COLS)
		_num_cols = cols;
	else
		_num_cols = MAX_COLS;
	if (rows <= MAX_ROWS)
		_num_rows = rows;
	else
		_num_rows = MAX_ROWS;

	for (int i=0; i<MAX_COLS; i++)
		_pinCol[i] = -1;
	for (int i=0; i<MAX_ROWS; i++)
		_pinRow[i] = -1;
	_delay = 0;

	if ((_num_cols == 4) and (_num_rows == 4))
	{
		setKeyChars(1, "123A");
		setKeyChars(2, "456B");
		setKeyChars(3, "789C");
		setKeyChars(4, "*0#D");
	}
	if ((_num_cols == 3) and (_num_rows == 4))
	{
		setKeyChars(1, "123");
		setKeyChars(2, "456");
		setKeyChars(3, "789");
		setKeyChars(4, "*0#");
	}
	if ((_num_cols == 3) and (_num_rows == 3))
	{
		setKeyChars(1, "123");
		setKeyChars(2, "456");
		setKeyChars(3, "789");
	}
}

void KeyPad::setColPins(int c0, int c1, int c2, int c3, int c4, int c5)
{
	_pinCol[0] = c0;
	_pinCol[1] = c1;
	_pinCol[2] = c2;
	_pinCol[3] = c3;
	_pinCol[4] = c4;
	_pinCol[5] = c5;

	for (int i=0; i<MAX_COLS; i++)
		if (_pinCol[i] != -1)
		{
			pinMode(_pinCol[i], OUTPUT);
			digitalWrite(_pinCol[i], LOW);
		}
}

void KeyPad::setRowPins(int r0, int r1, int r2, int r3, int r4)
{
	_pinRow[0] = r0;
	_pinRow[1] = r1;
	_pinRow[2] = r2;
	_pinRow[3] = r3;
	_pinRow[4] = r4;

	for (int i=0; i<MAX_ROWS; i++)
		if (_pinRow[i] != -1)
			pinMode(_pinRow[i], INPUT);
}

void KeyPad::setKeyChars(int r, char *chars)
{
	int nchars = strlen(chars);

	if ((r >= 1) and (r <= _num_rows))
		for (int i=0; i<nchars; i++)
			_chars[i][r-1] = chars[i];
}

void KeyPad::setDebounceDelay(int d)
{
	_delay = d;
}

char KeyPad::readKeys()
{
	int key = readRaw();

	if (key != -1)
		return _chars[(int)(key/10)-1][(key % 10)-1];
	else
		return 0;
}

int KeyPad::readRaw()
{
	int result = -1;

	for (int c=0; c<_num_cols; c++)
		if ((_pinCol[c] != -1) and (result == -1))
		{
			digitalWrite(_pinCol[c], HIGH);
			for (int r=0; r<_num_rows; r++)
				if ((_pinRow[r] != -1) and (result == -1))
					if (digitalRead(_pinRow[r])==HIGH)
					{
						result = ((c+1)*10)+(r+1);
						if (_delay != 0)
							delay(_delay);
						while (digitalRead(_pinRow[r])==HIGH) {};
					}
			digitalWrite(_pinCol[c], LOW);
		}

	return result;
}
