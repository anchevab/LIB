/* 
  Library for the HTU21D Humidity & Temp Sensor

  These displays use I2C to communicate, 2 pins are required to  
  interface
 
  This library uses code from the Adafruit Industries library
  (Limor Fried/Ladyada for Adafruit Industries.  )
  BSD license
 */

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define HTU21D_I2CADDR      0x40
#define HTU21D_READTEMP     0xE3
#define HTU21D_READHUM      0xE5
#define HTU21D_WRITEREG     0xE6
#define HTU21D_READREG      0xE7
#define HTU21D_RESET        0xFE


class HTU21D {
    public:
        HTU21D();
    boolean begin(void);
    
        void readSensor(void);
        float getHumidity(void);
        float getTemperature_C(void);
        float getTemperature_F(void);
        float getHeatIndex_C(void);
        float getHeatIndex_F(void);
    
 
    private:
        float readTemperature(void);
        float readHumidity(void);
        float computeHeatIndex_C(void);
        float computeHeatIndex_F(void);
        void reset(void);
        boolean readData(void);
    
        float humidity;
        float temperature_C;
        float temperature_F;
        float heatIndex_C;
        float heatIndex_F;

};

