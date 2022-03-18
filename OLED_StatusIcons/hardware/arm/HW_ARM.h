// Using Timer Counter 1, Channel 0

void OLED_StatusIcons::__start_interrupt()
{
	cli();																				// Disable interrupts
	PMC->PMC_WPMR = PMC_WPMR_WPKEY_VALUE;												// Disable PMC register write protection
	PMC->PMC_PCER0 = 1 << ID_TC3;														// Enable peripheral clock for TC1 Channel 0 (= ID_TC3)

	TcChannel* pTcCh = TC1->TC_CHANNEL + 0;												// Timer Counter 1, Channel 0
	pTcCh->TC_CCR = TC_CCR_CLKDIS;														// Disable TC clock
	pTcCh->TC_IDR = 0xFFFFFFFF;															// Disable interrupts
	pTcCh->TC_SR;																		// Clear status register
	pTcCh->TC_CMR = TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4;		// Set mode

	uint32_t rc = VARIANT_MCK/128/1000;													// Set frequency to 1kHz
	TC1->TC_CHANNEL[0].TC_RA = rc/2;													// Set RA to 50% of rc
	TC1->TC_CHANNEL[0].TC_RC = rc;														// Set RC to rc 
	pTcCh->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;										// Start counter
	TC1->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
	TC1->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
	NVIC->ISER[((uint32_t)(TC3_IRQn) >> 5)] = (1 << ((uint32_t)(TC3_IRQn) & 0x1F));		// Enable Timer Counter 1, Channel 0 (TC3_IRQn)
	sei();																				// Enable interrupts
}

void OLED_StatusIcons::__stop_interrupt()
{
	cli();										// Disable interrupts
	TC1->TC_CHANNEL->TC_CCR = TC_CCR_CLKDIS;	// Stop timer compare interrupt
	sei();										// Enable interrupts
}

void TC3_Handler()
{
	byte _topline;

	TC1->TC_CHANNEL->TC_SR;  // Read the status register to clear it
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
	sei();
}