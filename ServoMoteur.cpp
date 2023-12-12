#include "ServoMoteur.h"

ServoMoteur::ServoMoteur(int pin) {
  servo.attach(pin);
}

void ServoMoteur::setPosition(int angle) {
  servo.write(angle);
}


