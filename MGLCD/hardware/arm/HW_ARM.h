void MGLCD::_convert_float(char *buf, double num, int width, byte prec)
{
	char format[10];
	
	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}

void MGLCD::_data_direction(uint8_t dir)
{
	for (int i=0; i<8; i++)
		pinMode(DDR[i], dir);
}

void MGLCD::_get_DDR_pins(uint8_t _D0, uint8_t _D1, uint8_t _D2, uint8_t _D3, uint8_t _D4, uint8_t _D5, uint8_t _D6, uint8_t _D7)
{
	DDR[0] = _D0;
	DDR[1] = _D1;
	DDR[2] = _D2;
	DDR[3] = _D3;
	DDR[4] = _D4;
	DDR[5] = _D5;
	DDR[6] = _D6;
	DDR[7] = _D7;
}

