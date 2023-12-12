#ifndef CAPTEUR_ULTRASONIQUE_H
#define CAPTEUR_ULTRASONIQUE_H

#include "Ultrasonic.h"

class CapteurUltrasonique {
public:
  CapteurUltrasonique( int echoPin);
  long mesurerEnCentimetres();

private:
  Ultrasonic ultrasonic;
};

#endif  // CAPTEUR_ULTRASONIQUE_H
