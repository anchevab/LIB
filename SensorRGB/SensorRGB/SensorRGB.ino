/* DESCRIPCION
 *   Programa para manejar un sensor de color RGB.
 *   
 * NOTAS
 *   Repositorio: https://github.com/jorgemvc/SensorRGB
 *
 * MODIFICACIONES
 *   J.Villalobos  16.Jun.2017  Creación
 */
// ---- Bibliotecas
#include "SensorRGB.h"

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
  "Rojo",
  "Verde",
  "Azul",
  "Amarillo",
  "Negro",
  "Blanco",
  "Naranja"
};

void setup() {
  Serial.begin(9600);
  Serial.println("Sensor RGB");
  Serial.println("Jorge Villalobos C. - v1.0 - Jun.2017");
  Serial.println("");

  // Inicialización del sensor RGB
  Serial.println(rgb.inicio() ? "Sensor RGB encontrado": "Sensor RGB NO encontrado");
}  // void setup();

void loop() {
  // Realiza la lectura
  rgb.getRGBColor();
  Serial.print("Color detectado: ");
  
  // Determina por aproximacion el color
  Serial.print(getColor());
  
  // Despliega la composicion RGB del color detectado
  Serial.print(" | R:"); Serial.print(rgb.Red());
  Serial.print(" - G:"); Serial.print(rgb.Green());
  Serial.print(" - B:"); Serial.print(rgb.Blue());
  Serial.println("");
  delay(300);
}  // void loop()

String getColor() {
  int indice = -1;
  int dist = 10000,
      aux;
  
  // Calcula la distancia entre el color detectado y los
  // diferentes colores definidos, el que tenga menor distancia
  // sera el elegido.
  for (int i = 0 ; i < 7 ; i++) {
    aux = rgb.Diff(defColores[i][0], defColores[i][1], defColores[i][2]);
    if (aux < dist) {
      dist = aux;
      indice = i;
    }
  }

  return colores[indice];
}  // String GetColor()
