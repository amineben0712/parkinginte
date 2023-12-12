#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include "rgb_lcd.h"

class Afficheur {
public:
  Afficheur(int capacityMax);
  void initialiser();
  void fermer();
  void ouvert();
  void fermer1();
  void ouvert1();

private:
  rgb_lcd lcd;
  int capaciteMax;
};

class Vehicules
{
};

class Voiture : public Vehicules
{
};

class Camion : public Vehicules
{
};
#endif  // AFFICHEUR_H
