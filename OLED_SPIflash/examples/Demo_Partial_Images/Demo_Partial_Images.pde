// Demo_Partial_Images
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the loadBitmap()-function.
//
// This program requires OLED_SPIflash, OLED_I2C, 
// as well as SPIflash.
//
// This demo expects the "TestImages_Mono_Large" (MONO_L.SFD)
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

uint8_t  fileid = 0;
float    dx, dy;
int      steps, distX, distY;
uint16_t filetype, xOrigin, yOrigin, newX, newY, imgX, imgY;

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
  filetype = myFlash.getFileType(fileid);
  if (filetype == 6)
  {
    imgX = myFlash.getImageXSize(fileid);
    imgY = myFlash.getImageYSize(fileid);
    xOrigin = random(imgX-128);
    yOrigin = random(imgY-64);
    myFiles.loadBitmap(fileid, 0, 0, xOrigin, yOrigin, 128, 64);
    myOLED.update();
    delay(50);

    while (true)
    {
      newX = random(imgX-128);
      newY = random(imgY-64);
      distX = newX-xOrigin;
      distY = newY-yOrigin;
      if (abs(distX)>=abs(distY))
      {
        steps = abs(distX);
        if (newX>xOrigin)
          dx = 1;
        else
          dx = -1;
        dy = float(distY)/float(steps);
      }
      else
      {
        steps = abs(distY);
        if (newY>yOrigin)
          dy = 1;
        else
          dy = -1;
        dx = float(distX)/float(steps);
      }
      
      for (int i=0; i<steps; i++)
      {
        myFiles.loadBitmap(fileid, 0, 0, xOrigin+(dx*i), yOrigin+(dy*i), 128, 64);
        myOLED.update();
        delay(50);
      }
      xOrigin = newX;
      yOrigin = newY;
    }
  }
  else
  {
    myOLED.print("Incompatible file!", 0, 0);
    myOLED.update();
    while (true) {};
  }    
}


