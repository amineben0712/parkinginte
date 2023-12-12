#ifndef SERVO_MOTEUR_H
#define SERVO_MOTEUR_H

#include <Servo.h>

class ServoMoteur {
public:
  ServoMoteur(int pin);
  void setPosition(int angle);;
  
private:
  Servo servo;
};

#endif  // SERVO_MOTEUR_H
