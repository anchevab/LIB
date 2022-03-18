/* DESCRIPCION
 *   Implementación de la clase SensorRGB.
 * 
 * MODIFICACIONES
 *   J.Villalobos  16.Jun.2017  Creación
 */
#include "SensorRGB.h"
//                [ ---- Constructor ---- ]
SensorRGB::SensorRGB(){};

//                [ ---- Métodos ---- ]
bool SensorRGB::inicio(){
  return _tcs.begin();
}  // void inicio()

void SensorRGB::getRGBColor() {
  _tcs.setInterrupt(false);
  delay(60);
  _tcs.getRawData(&_r, &_g, &_b, &_c);
  _tcs.setInterrupt(true);
  
  // Convierte los valores obtenidos a valores RGB (0-255)
  _red = _r; _red /= _c; _red *= 256;
  _green = _g; _green /= _c; _green *= 256;
  _blue = _b; _blue /= _c; _blue *= 256;
}  // void getRGBColor()

uint16_t SensorRGB::Red(){
  return (uint16_t)_red;
}  // uint16_t Red()

uint16_t SensorRGB::Green(){
  return (uint16_t)_green;
}  // uint16_t Green()

uint16_t SensorRGB::Blue(){
  return (uint16_t)_blue;
}  // uint16_t Blue()

uint16_t SensorRGB::Clear(){
  return _c;
}  // uint16_t Clear()

// Calcula la distancia euclidiana del color detectado
// con el color RGB pasado como parametro
float SensorRGB::Diff(
  uint16_t r, uint16_t g, uint16_t b
) {
  return sqrt( sq(_red - r) + sq(_green - g) + sq(_blue - b));  
}  // float Diff()

