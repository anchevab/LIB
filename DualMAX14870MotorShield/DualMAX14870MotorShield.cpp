#include "DualMAX14870MotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////

DualMAX14870MotorShield::DualMAX14870MotorShield() :
  _nEN(4), _M1DIR(43), _M1PWM(45), _M2DIR(8), _M2PWM(10), _nFAULT(12)
{
}

DualMAX14870MotorShield::DualMAX14870MotorShield(uint8_t M1DIR,
                                                 uint8_t M1PWM,
                                                 uint8_t M2DIR,
                                                 uint8_t M2PWM,
                                                 uint8_t nEN,
                                                 uint8_t nFAULT) :
  _nEN(nEN), _M1DIR(M1DIR), _M1PWM(M1PWM),
  _M2DIR(M2DIR), _M2PWM(M2PWM), _nFAULT(nFAULT)
{
}


void DualMAX14870MotorShield::initPinsAndMaybeTimer()
{
  pinMode(_M1PWM, OUTPUT);
  digitalWrite(_M1PWM, LOW);
  pinMode(_M2PWM, OUTPUT);
  digitalWrite(_M2PWM, LOW);
  pinMode(_M1DIR, OUTPUT);
  digitalWrite(_M1DIR, LOW);
  pinMode(_M2DIR, OUTPUT);
  digitalWrite(_M2DIR, LOW);
  pinMode(_nEN, OUTPUT);
  digitalWrite(_nEN, LOW); // default to on
  pinMode(_nFAULT, INPUT_PULLUP);

#ifdef DUALMAX14870MOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    // timer 1 configuration
    // prescaler: clockI/O / 1
    // outputs enabled
    // phase-correct PWM
    // top of 400
    //
    // PWM frequency calculation
    // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
    TCCR1A = 0b10100000;
    TCCR1B = 0b00010001;
    ICR1 = 400;
  }
#endif
}

// speed should be a number between -400 and 400
void DualMAX14870MotorShield::setM1Speed(int16_t speed)
{
  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // max
    speed = 400;

#ifdef DUALMAX14870MOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    OCR1A = speed;
  }
  else
  {
    analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
  }
#else
  analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
#endif

  if (reverse ^ _flipM1) // flip if speed was negative or _flipM1 setting is active, but not both
    digitalWrite(_M1DIR, HIGH);
  else
    digitalWrite(_M1DIR, LOW);
}

// speed should be a number between -400 and 400
void DualMAX14870MotorShield::setM2Speed(int16_t speed)
{
  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // max PWM duty cycle
    speed = 400;

#ifdef DUALMAX14870MOTORSHIELD_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
  {
    OCR1B = speed;
  }
  else
  {
    analogWrite(_M2PWM, speed * 51 / 80); // map 400 to 255
  }
#else
  analogWrite(_M2PWM, speed * 51 / 80); // map 400 to 255
#endif

  if (reverse ^ _flipM2) // flip if speed was negative or _flipM2 setting is active, but not both
    digitalWrite(_M2DIR, HIGH);
  else
    digitalWrite(_M2DIR, LOW);
}

// set speed for both motors
// speed should be a number between -400 and 400
void DualMAX14870MotorShield::setSpeeds(int16_t m1Speed, int16_t m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}

void DualMAX14870MotorShield::flipM1(bool flip)
{
  _flipM1 = flip;
}

void DualMAX14870MotorShield::flipM2(bool flip)
{
  _flipM2 = flip;
}

bool DualMAX14870MotorShield::getFault()
{
  return !digitalRead(_nFAULT);
}

void DualMAX14870MotorShield::enableDrivers()
{
  digitalWrite(_nEN, LOW);
}

void DualMAX14870MotorShield::disableDrivers()
{
  digitalWrite(_nEN, HIGH);
}
