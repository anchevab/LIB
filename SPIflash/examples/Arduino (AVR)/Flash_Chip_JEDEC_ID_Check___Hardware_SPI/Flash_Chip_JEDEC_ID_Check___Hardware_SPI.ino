// Flash_Chip_JEDEC_ID_Check___Hardware_SPI 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program will attempt to read the JEDEC ID from
// the flash memory chip. If successful it will check
// if the chip is compatible with the SPIflash library.
//
// The chip must be connected to the hardware SPI pins.
//
// Board       |  MOSI  |  MISO  |  SCLK
// ---------------------------------------
// Uno         |   D11  |   D12  |   D13
// Mega        |   D51  |   D50  |   D52
// Due         |   D75  |   D74  |   D76
//
// The SPI jumper should be in the "Master" position.
// 

// Set the CE/SS pin here:
int _CE = 45;

#define SPI_CLOCK_MASK		0x03
#define SPI_2XCLOCK_MASK	0x01
uint8_t rate = 0x04;

struct _s_manufacturer
{
  uint8_t  _id;
  char     *_name;
};

struct _s_memtype
{
  uint8_t  _id;
  uint8_t  _m_id;
  char     *_name;
};

struct _s_device
{
  uint8_t  _id;
  uint8_t  _t_id;
  uint8_t  _m_id;
  uint8_t  _size;
  char     *_name;
};

_s_manufacturer _manufacturer[]=
{
  {0xBF, "SST/Microchip"},
  {0xEF, "Winbond"},
  {0xC2, "MXIC"}
};

_s_memtype _memtype[]=
{
  {0x25, 0xBF, "SPI Serial Flash"},
  {0x40, 0xEF, "SPI Serial Flash"},
  {0x20, 0xC2, "SPI Serial Flash"}
};

_s_device _device[]=
{
  {0x8C, 0x25, 0xBF, 0x02, "SST25VF020B"},
  {0x8D, 0x25, 0xBF, 0x04, "SST25VF040B"},
  {0x8E, 0x25, 0xBF, 0x08, "SST25VF080B"},
  {0x41, 0x25, 0xBF, 0x10, "SST25VF016B"},
  {0x4A, 0x25, 0xBF, 0x20, "SST25VF032B"},
  {0x4B, 0x25, 0xBF, 0x40, "SST25VF064C"},
  {0x14, 0x40, 0xEF, 0x08, "W25Q08BV"},
  {0x15, 0x40, 0xEF, 0x10, "W25Q16BV"},
  {0x16, 0x40, 0xEF, 0x20, "W25Q32BV"},
  {0x17, 0x40, 0xEF, 0x40, "W25Q64FV"},
  {0x18, 0x40, 0xEF, 0x80, "W25Q128BV/FV"},
  {0x15, 0x20, 0xC2, 0x10, "MX25L1605D"},
  {0x16, 0x20, 0xC2, 0x20, "MX25L3205D"},
  {0x17, 0x20, 0xC2, 0x40, "MX25L6405D"},
};

byte bt, b1, b2, b3;

boolean _printManu(uint8_t id, bool par=false)
{
  boolean found = false;
  
  if (par)
    Serial.print(" (");
  for(int i = 0; i<(sizeof(_manufacturer)/sizeof(struct _s_manufacturer)); i++)
  {
    if (_manufacturer[i]._id==id)
    {
      found = true;
      Serial.print(_manufacturer[i]._name);
      if (par)
        Serial.println(")");
      else
        Serial.println();
    }
  }
  if (!found)
  {
      Serial.print("Unknown/Unsupported");
      if (par)
        Serial.println(")");
      else
        Serial.println();
  }
  
  return found;
}

boolean _printMemType(uint8_t id, uint8_t mid, bool par=false)
{
  boolean found = false;
  
  if (par)
    Serial.print(" (");
  for(int i = 0; i<(sizeof(_memtype)/sizeof(struct _s_memtype)); i++)
  {
    if ((_memtype[i]._id==id) & (_memtype[i]._m_id==mid))
    {
      found = true;
      Serial.print(_memtype[i]._name);
      if (par)
        Serial.println(")");
      else
        Serial.println();
    }
  }
  if (!found)
  {
      Serial.print("Unknown/Unsupported");
      if (par)
        Serial.println(")");
      else
        Serial.println();
  }
  
  return found;
}

boolean _printDevice(uint8_t id, uint8_t tid, uint8_t mid, bool par=false)
{
  boolean found = false;
  
  if (par)
    Serial.print(" (");
  for(int i = 0; i<(sizeof(_device)/sizeof(struct _s_device)); i++)
  {
    if ((_device[i]._id==id) & (_device[i]._m_id==mid) & (_device[i]._t_id==tid))
    {
      found = true;
      Serial.print(_device[i]._name);
      Serial.print(", ");
      Serial.print(_device[i]._size, DEC);
      Serial.print("MBit");
      if (par)
        Serial.println(")");
      else
        Serial.println();
    }
  }
  if (!found)
  {
      Serial.print("Unknown/Unsupported");
      if (par)
        Serial.println(")");
      else
        Serial.println();
  }
  
  return found;
}

byte _readByte()
{
  SPDR = 0x00;
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}

void _writeByte(uint8_t value)
{
  SPDR = value;
  while(!(SPSR & (1<<SPIF)));
}

void setup()
{
  digitalWrite(SS, HIGH);
  pinMode(SS, OUTPUT);
  digitalWrite(_CE, HIGH);
  pinMode(_CE, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
  
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((rate >> 2) & SPI_2XCLOCK_MASK);

  Serial.begin(115200);
}

void loop()
{
  delay(1000);
  Serial.println("*****************************");
  Serial.println("* Flash Chip JEDEC ID Check *");
  Serial.println("*****************************");
  Serial.println();
  digitalWrite(_CE, LOW);
  _writeByte(0x9F);      // JEDEC Read-ID

  b1=_readByte();
  b2=_readByte();
  b3=_readByte();
  digitalWrite(_CE, HIGH);
  
  Serial.print("Manufacturers ID:< 0x");
  Serial.print(b1, HEX);
  if (_printManu(b1, true))
  {
    Serial.print("Memory type     :< 0x");
    Serial.print(b2, HEX);
    if (_printMemType(b2, b1, true))
    {
      Serial.print("Device ID       :< 0x");
      Serial.print(b3, HEX);
      _printDevice(b3, b2, b1, true);
    }
  }
  Serial.println();
  Serial.println("*****************************");
  Serial.println();
  
  while (1) {};
}


