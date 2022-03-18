void MGLCD::_convert_float(char *buf, double num, int width, byte prec)
{
	dtostrf(num, width, prec, buf);
}

void MGLCD::_data_direction(uint8_t dir)
{
	if (dir==INPUT)
		for (int i=0; i<8; i++)
			*DD_DB[i] &= ~B_DB[i];
	else
		for (int i=0; i<8; i++)
			*DD_DB[i] |= B_DB[i];
}

void MGLCD::_get_DDR_pins(uint8_t _D0, uint8_t _D1, uint8_t _D2, uint8_t _D3, uint8_t _D4, uint8_t _D5, uint8_t _D6, uint8_t _D7)
{
	DD_DB[0] = portModeRegister(digitalPinToPort(_D0));
	DD_DB[1] = portModeRegister(digitalPinToPort(_D1));
	DD_DB[2] = portModeRegister(digitalPinToPort(_D2));
	DD_DB[3] = portModeRegister(digitalPinToPort(_D3));
	DD_DB[4] = portModeRegister(digitalPinToPort(_D4));
	DD_DB[5] = portModeRegister(digitalPinToPort(_D5));
	DD_DB[6] = portModeRegister(digitalPinToPort(_D6));
	DD_DB[7] = portModeRegister(digitalPinToPort(_D7));
}
