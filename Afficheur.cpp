#include "Afficheur.h"

Afficheur::Afficheur(int capacityMax) : capaciteMax(capacityMax) {}

void Afficheur::initialiser() {
  lcd.begin(16, 2);
  //lcd.print("Places dispo: ");
  //lcd.print(capaciteMax);
}

void Afficheur::fermer() {
  if (capaciteMax > 0) {
    capaciteMax--;
    lcd.clear();
    lcd.print("  parking_int ");
  //  lcd.print(capaciteMax);
  }
}

void Afficheur::ouvert() {
  if (capaciteMax < 100) {
    capaciteMax++;
    lcd.clear();
    lcd.print("veuillez entrez");
   // lcd.print(capaciteMax);
  }
}
