void OLED_StatusIcons::__start_interrupt()
{
	noInterrupts();											// Disable interrupts
	OpenTimer1(T1_ON | T1_PS_1_64 | T1_SOURCE_INT, 1225);	// Set up timer compare interrupt 1 (Prescaler = 64, Trigger rate = 1kHz approx.)
	ConfigIntTimer1((T1_INT_ON | T1_INT_PRIOR_3));			// Enable timer compare interrupt 1, Priority 3
	interrupts();											// Enable interrupts

}

void OLED_StatusIcons::__stop_interrupt()
{
	noInterrupts();											// Disable interrupts
	OpenTimer1(T1_OFF, 0);									// Disable timer compare interrupt
	interrupts();											// Enable interrupts
}

#ifdef __cplusplus
extern "C" {
#endif
	void __ISR(_TIMER_1_VECTOR,IPL3AUTO) marquee_handler(void)
	{
		byte _topline;

		noInterrupts();		// Disable interrupts
		mT1ClearIntFlag();  // Clear interrupt flag

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
							data=_icons[i].bitmap[cx+((cy/8)*sx)];
							if ((data & (1<<bit))>0)
								_OLED->clrPixel(x+cx, y+cy);
						}
					}      
				}
			}
			_int_counter = 0;
			_OLED->update();
		}

		interrupts();	// Enable interrupts
	}
#ifdef __cplusplus
}
#endif
