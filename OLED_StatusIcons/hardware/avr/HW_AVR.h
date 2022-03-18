void OLED_StatusIcons::__start_interrupt()
{
	cli();						// Disable interrupts
	TCCR2A = 0;					// Clear TCCR2A
	TCCR2B = 0;					// Clear TCCR2B
	TCNT2  = 0;					// Clear counter value
	OCR2A = 249;				// = (16*10^6) / (1000*64) - 1 (for 1kHz)
	TCCR2A |= (1 << WGM21);		// Enable CTC mode
	TCCR2B |= (1 << CS22);		// Set CS22 bit for 64 prescaler
	TIMSK2 |= (1 << OCIE2A);	// Enable timer compare interrupt
	sei();						// Enable interrupts
}

void OLED_StatusIcons::__stop_interrupt()
{
	cli();						// Disable interrupts
	TIMSK2 = 0;					// Disable timer compare interrupt
	sei();						// Enable interrupts
}

ISR(TIMER2_COMPA_vect)
{
	byte _topline;

	cli();
	_int_counter++;
	if (_int_counter == _int_speed)
	{
		if ((_position & 0x02) == 0)
		{
			for (byte y = 0; y < (_size == ICONSIZE_8X8?8:16); y++)
				_OLED->drawLine(0, y, 128, y);
			_topline = 0;
		}
		else
		{
			_topline = (_size == ICONSIZE_8X8?56:48);
			for (byte y = _topline; y < 64; y++)
				_OLED->drawLine(0, y, 128, y);
		}

		for (byte i = 0; i <= _max_icon; i++)
		{
			if ((_icons[i].bitmap != 0) and (_icons[i].enabled))
			{
				byte sx, sy;
				byte x;
				byte y = _topline;
				byte data, bit;

				sx = sy = (_size == ICONSIZE_8X8?8:16);
				if ((_position & 0x01) == 1)
					x = ((sx + 1) * i) + 1;
				else
					x = 127 - ((sx + 1) * (i + 1));
				for (int cy=0; cy<sy; cy++)
				{
					bit= cy % 8;
					for(int cx=0; cx<sx; cx++)
					{
						data=pgm_read_byte(&_icons[i].bitmap[cx+((cy/8)*sx)]);
						if ((data & (1<<bit))>0)
							_OLED->clrPixel(x+cx, y+cy);
					}
				}      
			}
		}
		_int_counter = 0;
		_OLED->update();
	}
	sei();
}