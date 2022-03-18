# Tb67h420ftg
Arduino library for Pololu/Toshiba tb67h420ftg motor driver breakout board.

Please note that this library is very new. I am calling it "Version zero"
until I get more reports from others that it works for them. My testing was
done on a generic ARM M3 development board (STM32F103C8 "Blue Pill") so you will
have to CHANGE THE PIN ASSIGNMENTS in the dot.h file
 
Provides the following:
  * Tb67h420ftg()
  * Tb67h420ftg(byte directA, byte directB)
  * void go(byte motor, byte direct, int pwm)
  * void brake(byte motor)
  * void coast(byte motor)
  * int  getStatus()
  * void clearFault(byte motor)`
  * void setInstalledDirection(byte motor, byte direct)


