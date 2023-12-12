#ifndef BARRIERE_H
#define BARRIERE_H

#include "CapteurUltrasonique.h"
#include "ServoMoteur.h"
#include "Afficheur.h"

class Barriere {
public:
  Barriere( int echoPin, int servoPin, Afficheur& afficheur);
  void tick();

private:
  CapteurUltrasonique capteur;
  ServoMoteur myServo;
  Afficheur& afficheur;
  bool servirVehicule;
};

#endif
