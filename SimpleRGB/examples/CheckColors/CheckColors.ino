/** @file    CheckColors
 *  @author  Jorge Villalobos Carvajal (jorgemvc@gmail.com)
 *  @date    16.Jun.2017  
 *  @version 1.0 
 *  
 *  @brief   How to use the library SensorRGB.
 *
 *  @licence  MIT License
 */// ---- Bibliotecas
#include <SensorRGB.h>

// ---- Variables
SensorRGB rgb;
// Matriz con la deficion RGB de los colores
uint16_t defColores[7][3] = {
  {255, 0  , 0  },
  {0  , 255, 0  },
  {0  , 0  , 255},
  {255, 255, 102},
  {0  , 0  , 0  },
  {255, 255, 255},
  {255, 178, 102}
};
// Nombre correspondiente de los colores definidos
String colores[7] = {
  "Red",
  "Green",
  "Blue",
  "Yellow",
  "Black",
  "White",
  "Orange"
};

void setup() {
  Serial.begin(9600);
  Serial.println("Simple RGB");
  Serial.println("Jorge Villalobos C. - v1.0 - Jun.2017");
  Serial.println("");

  // Inicialización del sensor RGB
  Serial.println(rgb.begin() ? "Sensor TCS34725 found": "TCS34725 Sensor NOT FOUND !!!");
}  // void setup();

void loop() {
  // Do the color reading
  rgb.getRGBColor();
  Serial.print("Detected color: ");
  
  // Determine the color by approximation
  Serial.print(getColor());
  
  // Displays the RGB composition of the detected color
  Serial.print(" | R:"); Serial.print(rgb.red());
  Serial.print(" - G:"); Serial.print(rgb.green());
  Serial.print(" - B:"); Serial.print(rgb.blue());
  Serial.println("");
  delay(300);
}  // void loop()

String getColor() {
  int indice = -1;
  int dist = 10000,
      aux;
  
  // Calculate the distance between the detected color and the 
  // different defined colors, the one with the shortest distance
  // will be the chosen one.
  for (int i = 0 ; i < 7 ; i++) {
    aux = rgb.diff(defColores[i][0], defColores[i][1], defColores[i][2]);
    if (aux < dist) {
      dist = aux;
      indice = i;
    }
  }

  return colores[indice];
} // String GetColor()
