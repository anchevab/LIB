/*
  Library for the HTU21D Humidity & Temp Sensor

  These displays use I2C to communicate, 2 pins are required to  
  interface

  This library uses code from the Adafruit Industries library
  (Limor Fried/Ladyada for Adafruit Industries.  )
  BSD license
 */

#include "cactus_io_HTU21D.h"
#include <util/delay.h>

HTU21D::HTU21D() {
}


boolean HTU21D::begin(void) {
  Wire.begin();
  
  reset();

  Wire.beginTransmission(HTU21D_I2CADDR);
  Wire.write(HTU21D_READREG);
  Wire.endTransmission();
  Wire.requestFrom(HTU21D_I2CADDR, 1);
  return (Wire.read() == 0x2); // after reset should be 0x2
}

void HTU21D::readSensor(void) {
    humidity = readHumidity();
    temperature_C = readTemperature();
    temperature_F = temperature_C * 1.8 + 32;
}

float HTU21D::getHumidity(void) {
    return humidity;
}

float HTU21D::getTemperature_C(void) {
    return temperature_C;
}

float HTU21D::getTemperature_F(void) {
    return temperature_F;
}

float HTU21D::getHeatIndex_C(void) {
    return computeHeatIndex_C();
}

float HTU21D::getHeatIndex_F(void) {
    return computeHeatIndex_F();
}

void HTU21D::reset(void) {
    Wire.beginTransmission(HTU21D_I2CADDR);
    Wire.write(HTU21D_RESET);
    Wire.endTransmission();
    delay(15);
}

float HTU21D::readTemperature(void) {
  
  Wire.beginTransmission(HTU21D_I2CADDR);
  Wire.write(HTU21D_READTEMP);
  Wire.endTransmission();
  
  delay(50); // add delay between request and actual read!
  
  Wire.requestFrom(HTU21D_I2CADDR, 3);
  while (!Wire.available()) {}

  uint16_t t = Wire.read();
  t <<= 8;
  t |= Wire.read();

  uint8_t crc = Wire.read();

  float temp = t;
  temp *= 175.72;
  temp /= 65536;
  temp -= 46.85;

  return temp;
}
  

float HTU21D::readHumidity(void) {
  // OK lets ready!
  Wire.beginTransmission(HTU21D_I2CADDR);
  Wire.write(HTU21D_READHUM);
  Wire.endTransmission();
  
  delay(50); // add delay between request and actual read!
  
  Wire.requestFrom(HTU21D_I2CADDR, 3);
  while (!Wire.available()) {}

  uint16_t h = Wire.read();
  h <<= 8;
  h |= Wire.read();

  uint8_t crc = Wire.read();

  float hum;
  hum = h;
  hum *= 125;
  hum /= 65536;
  hum -= 6;

  return hum;
}


float HTU21D::computeHeatIndex_C(void) {
    // Wikipedia: http://en.wikipedia.org/wiki/Heat_index
    return -8.784695 +
    1.61139411 * temperature_C +
    2.33854900 * humidity +
    -0.14611605 * temperature_C*humidity +
    -0.01230809 * pow(temperature_C, 2) +
    -0.01642482 * pow(humidity, 2) +
    0.00221173 * pow(temperature_C, 2) * humidity +
    0.00072546 * temperature_C * pow(humidity, 2) +
    -0.00000358 * pow(temperature_C, 2) * pow(humidity, 2);
}

float HTU21D::computeHeatIndex_F(void) {
    // Adapted from equation at: https://github.com/adafruit/DHT-sensor-library/issues/9 and
    // Wikipedia: http://en.wikipedia.org/wiki/Heat_index
    return -42.379 +
    2.04901523 * temperature_F +
    10.14333127 * humidity +
    -0.22475541 * temperature_F*humidity +
    -0.00683783 * pow(temperature_F, 2) +
    -0.05481717 * pow(humidity, 2) +
    0.00122874 * pow(temperature_F, 2) * humidity +
    0.00085282 * temperature_F*pow(humidity, 2) +
    -0.00000199 * pow(temperature_F, 2) * pow(humidity, 2);
}
