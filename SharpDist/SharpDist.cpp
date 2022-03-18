#include<SharpDist.h>
#include<Arduino.h>

SharpDist::SharpDist(int pin) {
    this->pin = pin;
    this->samples = 1;
}

SharpDist::SharpDist(int pin, int samples) {
    this->pin = pin;
    this->samples = samples;
}

void SharpDist::setSamples(int samples) {
    this->samples = samples;
}

float SharpDist::dist() {
    float sum = 0;
    for(int i = 0; i < samples; i++) {
        sum += analogRead(pin);
    }

    float voltage = 5 * (sum / (samples * 4096.0));

    return 1.0/voltage;
}

float SharpDist::distanceCentimeters() {
    return 33.02*dist();
}

float SharpDist::distanceInches() {
    return 13.0*dist();
}
