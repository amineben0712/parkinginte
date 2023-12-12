#include "CapteurUltrasonique.h"

CapteurUltrasonique::CapteurUltrasonique(int echoPin)
  : ultrasonic( echoPin) {}

long CapteurUltrasonique::mesurerEnCentimetres() {
  return ultrasonic.MeasureInCentimeters();
}
