/** @file    SimpleRGB.cpp
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    16.Jun.2017  
 *  @version 1.0 
 *  
 *  @requires  Adafruit_TCS34725 library installed.
 *  @brief   Libray for simplify use of Adafruit TCS34725.
 *
 *  @licence  MIT License
 */
#include "SimpleRGB.h"
//                [ ---- Constructor ---- ]
SensorRGB::SensorRGB(){};

//                [ ---- Methods ---- ]
bool SensorRGB::begin(){
  return _tcs.begin();
}  // void begin()

void SensorRGB::getRGBColor() {
  _tcs.setInterrupt(false);
  delay(60);
  _tcs.getRawData(&_r, &_g, &_b, &_c);
  _tcs.setInterrupt(true);
  
  // Convert the values obtained to valid RGB values (0-255)
  _red = _r; _red /= _c; _red *= 255;
  _green = _g; _green /= _c; _green *= 255;
  _blue = _b; _blue /= _c; _blue *= 255;
}  // void getRGBColor()

uint16_t SensorRGB::red(){
  return (uint16_t)_red;
}  // uint16_t red()

uint16_t SensorRGB::green(){
  return (uint16_t)_green;
}  // uint16_t green()

uint16_t SensorRGB::blue(){
  return (uint16_t)_blue;
}  // uint16_t blue()

uint16_t SensorRGB::clear(){
  return _c;
}  // uint16_t clear()

// ---- Calculate the Euclidean distance of the detected color 
//      with the color RGB passed as a parameter
float SensorRGB::diff(
  uint16_t r, uint16_t g, uint16_t b
) {
  return sqrt( sq(_red - r) + sq(_green - g) + sq(_blue - b));  
} // float diff()
