#include<SharpDist.h>

SharpDist dist(36, 10);

void setup() {
    Serial.begin(9600);
}

void loop() {
    float distance = dist.distanceCentimeters();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}
