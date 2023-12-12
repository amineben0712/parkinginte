#include "Barriere.h"
#include "Afficheur.h"


// Créer les afficheurs associés à chaque barrière
Afficheur afficheurIn(9);
Afficheur afficheurOut(9);

// Créer les barrières avec leurs capteurs, servo-moteurs et afficheurs
Barriere barriereIn(6, 3, afficheurIn);
Barriere barriereOut(2, 7, afficheurOut);

void setup() {
  Serial.begin(9600);

  // Initialiser les afficheurs
  afficheurIn.initialiser();
  afficheurOut.initialiser();
}

void loop() {
  // Appeler la fonction tick pour chaque barrière
  barriereIn.tick();
  barriereOut.tick();
}
/*//Redéfinition d'opérateur
// class Servo {
//    Servo & operator ++(int){
//       myServo->write(180);
//    return(*this);}
//    Servo & operator --(int){
//       myServo->write(0);
//    return(*this);}
//}

Parking* parking;
Afficheur* afficheur;

void setup()
{
  lcd.begin(16, 2);
  parking = new Parking;
}

void loop()
{
  try
  {
    parking->tick();
  }
  catch (int erreur)
  {
    if (erreur == 1) {
      afficheur->print("Erreur capacité max");
    }
    else {
      afficheur->print("Exception inconnue");
    }
  }
}*/