#include "Barriere.h"
#include "CapteurUltrasonique.h"
#include "ServoMoteur.h"
#include "Afficheur.h"

Barriere::Barriere(int echoPin, int servoPin, Afficheur& afficheur)
    : capteur( echoPin), myServo(servoPin), afficheur(afficheur) {}

void Barriere::tick() {
  long rangeInCentimeters = capteur.mesurerEnCentimetres();

  if (rangeInCentimeters < 20) {
    myServo.setPosition(360);
    afficheur.ouvert();
  } else {
    myServo.setPosition(0);
    afficheur.fermer();
    
  }
}
