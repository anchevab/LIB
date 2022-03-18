// Demo_Images_1
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the loadBitmap()-function.
//
// This program requires OLED_SPIflash, OLED_I2C, 
// as well as SPIflash.
//
// This demo expects the "TestImages_OLED" (OLED.SFD)
// dataset to be loaded into the flash chip.
// (This dataset is supplied with the OLED_SPIflash
// library and can be found in the DataSet folder)
//

#include <SPIflash.h>
#include <OLED_I2C.h>
#include <OLED_SPIflash.h>

// Remember to set the appropriate pins for your setup.
// See the OLED_I2C manual for further information.
// myOLED(<SDA>, <SCL>, <RST>);
OLED          myOLED(SDA,SCL,8);

// myFlash(<SS>); (if using the hardware SPI pins. See the SPIflash manual for other configurations.)
SPIflash      myFlash(53);

OLED_SPIflash myFiles(&myOLED, &myFlash);

// Declare which fonts we will be using
extern uint8_t TinyFont[];

uint8_t  fileid, xPos, yPos;
uint16_t filetype;

void setup()
{
  randomSeed(analogRead(0));
  
  myOLED.begin();
  myOLED.clrScr();
  myOLED.setFont(TinyFont);
  myFlash.begin();

  if (myFlash.ID_device==0)
  {
    myOLED.print("Unknown flash device!", 0, 0);
    myOLED.update();
    while (true) {};
  }    
}

void loop()
{
  fileid = 0;
  filetype = 0;

  while (filetype != ERR_FILE_DOES_NOT_EXIST)
  {
    filetype = myFlash.getFileType(fileid);
    if (filetype == 6)
    {
      myOLED.clrScr();
      xPos = 64-(myFlash.getImageXSize(fileid)/2);
      yPos = 32-(myFlash.getImageYSize(fileid)/2);
      myFiles.loadBitmap(fileid, xPos, yPos);
      myOLED.update();
      delay(2000);
      fileid++;
    }
  }
}


