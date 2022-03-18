
#include "Tb67h402ftg.h"

// Create an instance of a motor driver.
Tb67h420ftg Motor;

/* 
   Written 2018 by Chris Albertson.  Copyright is released to the public domain
   You may redistribute or modify this example program without restrictions.
 */

int motorStatus = 0;
const byte pwmMedium = 100;

void setup() {

  Serial.begin(9600);
  Serial.println("--START--");
}

void loop() {
  // This loop will cycle through some basic tests of your motor, the
  // driver chip and your wirring.  We define "clockwise" to mean that
  // when looking at the end of the motor shaft it appears to move in 
  // the CW direction.   If it mores the wrong way, either swap the motor
  // lead wires or if you can't do that use either the setInstalledDirection()
  // method or the constructor that allows you to specify an intalled
  // direction.and specify "CCW" as the installed direction.   After
  // this the motor will spin CW when you tell it to spin CW.
  //
  // The setInstalledDirection() method is also usful if you whish to
  // use the convetion were direction is defined from one side of a vehicle
  // such that setting the heel direction to CW for both motors cause
  // the vehicle to move forward.
  

  // Run motor "A" forward and motor "B" backwards at medium speed
  // for 10 seconds.
  Serial.println("Spinning moters for 10 seconds., A=CW, B=CCW");
  Motor.go(MOTOR_A, CW,  pwmMedium);
  Motor.go(MOTOR_B, CCW, pwmMedium);
  delay(10000);

  // Let the motors coat to a stop for 10 seconds
  // This effectivly opens or disconnects the leads.  You should be able to
  // turn the shaft of a small motr by hand.
  Serial.println("Coasting moters for 10 seconds.");
  Motor.coast(MOTOR_A);
  Motor.coast(MOTOR_B);
  delay(10000);

  // Runs the moters in the oposit directions as before
  // but at the same speed.
  Serial.println("Spining moters for 10 seconds, A=CCW, B=CW");
  Motor.go(MOTOR_A, CCW, pwmMedium);
  Motor.go(MOTOR_B, CW,  pwmMedium);
  delay(10000);

  // Brake the motors.  This should cause an abrupt stop and the 
  // motor shafts sould be locked and hard to turn by hand
  Serial.println("Braking moters for 10 seconds");
  Motor.brake(MOTOR_A);
  Motor.brake(MOTOR_B);
  delay(10000);
  
  // Get the status from the driver chip.  It will print out 
  // number.  See the header file to interpet the number but the
  // short answer is that "0" means "no error".
  Serial.print("Driver status = ");
  motorStatus = Motor.getStatus();
  Serial.println(motorStatus);
  delay(2000);
}
