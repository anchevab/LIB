/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "Arduino.h"
#include "Monitor.h"



Monitor::Monitor(){}

/* Service routine ; writes coded message : c=code, d=destination, v=value */ 
void Monitor::writeMess(byte c,byte d,int v)
{
    mess[0]=(c<<4)+d;
    mess[0]=mess[0]|128;
    mess[2]=v;
    mess[2]=mess[2]&127;
    mess[1]=v>>7;
    Serial.write(mess,3);
}

/* Service routine ; ask for answer message. Timout 30 mSec */
byte Monitor::readAnsw()
{
    int i;
    for (i=0;i<30;i++)
    {
      delay(1);
      if (Serial.available()) return Serial.read();
    } 
   return 0; 
}

/* Open serial communication with monitor at 'baud' speed */
void Monitor::openM(long baud)
{
   Serial.begin(baud);
}

/* Close serial communication */
void Monitor::closeM()
{
    Serial.end();
}

/* Send analogic value (integer 0 to 1024) to destination d (byte 3 to 13)*/
void Monitor::writeAna(int v,byte d)
{
    writeMess(2,d,v);
}

/* Send digital value (integer 1/0) to destination d (byte 3 to 13) */
void Monitor::writeDig(int v,byte d)
{
    writeMess(0,d,v);
}

/* Plot value (integer 0 to 1024) to trace d (byte 0 to 5) */
void Monitor::plotFun(int v,byte d)
{
    writeMess(4,d,v);
}

/* Reset trace d (0 to 5) ; but if d=6 reset all traces */
void Monitor::plotReset(byte d)
{
    writeMess(5,d,0);
}

/* Function f1. Plot value f2  (in function of f1 ) */
void Monitor::plotFunX(int v)
{
    writeMess(6,0,v);
}

/* Function f2. Plot value f2  (in function of f1 ) */ 
void Monitor::plotFunY(int v)
{
    writeMess(6,1,v);
}

/* Returns digital value (0/1) of destination button  d (byte 3 to 13) */
byte Monitor::readDig(byte d)
{
    writeMess(1,d,0);
    return readAnsw();
}

/* Returns value (0 to 255) of destination PWM slides d (3,5,6,9,10,11) */
byte Monitor::readPWM(byte d)
{
    writeMess(3,d,0);
    return readAnsw();
}
