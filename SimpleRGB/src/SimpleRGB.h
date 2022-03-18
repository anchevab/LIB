/** @file    SimpleRGB.h
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    16.Jun.2017  
 *  @version 1.0 
 *  
 *  @requires  Adafruit_TCS34725 library installed.
 *  @brief   Libray for simplify use of Adafruit TCS34725.
 *
 *  @licence  MIT License
 */
#include <Arduino.h>
#include <Adafruit_TCS34725.h>
#ifndef SENSORRGB_H
#define SENSORRGB_H
class SensorRGB {
   public:
     // ---- Constructors
     SensorRGB();
  
     // ---- Methods
     bool     begin();
     void     getRGBColor();
     uint16_t red();
     uint16_t green();
     uint16_t blue();
     uint16_t clear();
     float    diff(uint16_t r, uint16_t g, uint16_t b);
     
   private:
     uint16_t  _r,
               _g,
               _b,
               _c;
     float     _red,
               _green,
               _blue;
     Adafruit_TCS34725 _tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
 };
#endif
