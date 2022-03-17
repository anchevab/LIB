/*
 *	Sharp GP2Y0A02YK0F IR Distance Sensor 20-150 cm 
 *	(Parallax Part Number: #28997) 
 *	IR Distance Sensor Library
 */

#include <GP2Y0A02YK0F.h>

// Constructor

GP2Y0A02YK0F::GP2Y0A02YK0F() {

}

// Default Begin method: sensorPin = A0.

void GP2Y0A02YK0F::begin() {
	begin (A0);
}

// Begin method - assign sensorPin as the analog sensor input
// When you use begin() without variables the default input A0 is assumed.

void GP2Y0A02YK0F::begin(int sensorPin) {
  	pinMode(sensorPin, INPUT);
	_sensorPin = sensorPin;
}

// getDistanceRaw() Method: Returns the distance as a raw value: ADC output: 0 -> 1023

int GP2Y0A02YK0F::getDistanceRaw() {
		return (analogRead(_sensorPin));
}

// getDistanceCentimeter() Method: Returns the distance in centimeters

int GP2Y0A02YK0F::getDistanceCentimeter() {
	float sensorValue = analogRead(_sensorPin);
  	float cm = 10650.08 * pow(sensorValue,-0.935) - 10;
  	return roundf(cm);
}

// isCloser Method: check whether the distance to the detected object is smaller than a given threshold

boolean GP2Y0A02YK0F::isCloser(int threshold) {
	if (threshold>getDistanceCentimeter()) {
		return (true);
	} else {
		return (false);
	}
}

// isFarther Method: check whether the distance to the detected object is smaller than a given threshold

boolean GP2Y0A02YK0F::isFarther(int threshold) {
	if (threshold<getDistanceCentimeter()) {
		return true;
	} else {
		return false;
	}
}