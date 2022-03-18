// Demo_Images_2
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the loadBitmap()-function.
//
// This program requires OLED_SPIflash, OLED_I2C, 
// as well as SPIflash.
//
// This demo expects the "TestImages_Mono" (MONO.SFD)
// dataset to be loaded into the flash chip.
// (Demo datasets are supplied with the SPIflash library)
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
      xPos = random(84-myFlash.getImageXSize(fileid));
      yPos = random(48-myFlash.getImageYSize(fileid));
      myFiles.loadBitmap(fileid, xPos, yPos);
      myOLED.update();
      delay(500);
      fileid++;
    }
  }
}


