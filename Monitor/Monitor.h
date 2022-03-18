/*


*/
#ifndef Monitor_h
#define Monitor_h

#include "Arduino.h"

class Monitor
{
   public:
    Monitor();
    void openM(long baud);
    void closeM();
    void writeAna(int v,byte d);
    void writeDig(int v,byte d);
    void plotFun(int v,byte d);
    void plotReset(byte d);
    void plotFunX(int v);
    void plotFunY(int v);
    byte readDig(byte d);
    byte readPWM(byte d);
   private:
    void writeMess(byte c,byte d,int v);
    byte readAnsw();
    byte mess[3];
};


#endif

