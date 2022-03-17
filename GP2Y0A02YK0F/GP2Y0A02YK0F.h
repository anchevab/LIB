/*
 *	Sharp GP2Y0A02YK0F IR Distance Sensor 20-150 cm 
 *	(Parallax Part Number: #28997) 
 *	IR Distance Sensor Library
 *
 *  Written By:	David Such (Reefwing Software - http://www.reefwing.com.au/)
 *  Version: 	1.0
 *  Date:    	1st November 2015
 *
 *	Version History:
 *		1.0		01/11/15	Original release
 *
 *  Instructions:
 *    - Create a directory called GP2Y0A02YK0F within the libraries sub directory where your Arduino sketches are saved.
 *    - Copy GP2Y0A02YK0F.h, GP2Y0A02YK0F.cpp and keywords.txt into the GP2Y0A02YK0F directory.
 *    - Within the GP2Y0A02YK0F directory, create a sub directory called examples.
 *    - Copy DisplayCM.ino into the examples sub directory.
 *    - Restart the Arduino IDE to see the new library.
 *
 *  Read More:
 *    - Visit http://reefwingrobotics.blogspot.com.au/
 */

#ifndef GP2Y0A02YK0F_h
#define GP2Y0A02YK0F_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

class GP2Y0A02YK0F
{
	public:
		GP2Y0A02YK0F();
		void begin();
		void begin(int sensorPin);
		int getDistanceRaw();
		int getDistanceVolt();
		int getDistanceCentimeter();

		boolean isCloser(int threshold);
		boolean isFarther(int threshold);

	private:
		int _sensorPin;
};
#endif