#include <GP2Y0A02YK0F.h>
#define IR 34

GP2Y0A02YK0F irSensor;
int distance;

void setup()
{
  Serial.begin(115200);
  irSensor.begin(IR);	//	Assign analog as sensor pin
}

void loop()
{
  distance = irSensor.getDistanceCentimeter();
  Serial.print("\nDistance in centimeters: ");
  Serial.print(distance);  
  delay(500); 
}