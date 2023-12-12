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
