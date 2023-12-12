#include <Adafruit_RGBLCDShield.h>
//#include <rgb_lcd.h>
#include <Servo.h>
#include <Adafruit_RGBLCDShield.h>

#ifndef PARKING_H
#define PARKING_H

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
//#include "rgb_lcd.h"

#define CAPACITY_MAX 9
#define B_IN  0
#define B_OUT 1
#define SOUND_VELOCITY 0.034

// Declaration of the Capteur class
class Capteur
{
  const int trigPin;
  const int echoPin;
  long duration;
  float distanceCm;
public:
  Capteur(int tPin, int ePin);

  bool getStatus();
};

// Declaration of the Barriere class
class Barriere
{
protected:
  int* nbrPlacesLibres;
  Capteur* capteur;
public:
  virtual ~Barriere() {}
  virtual bool isThereAvehicule() = 0;
  bool servirVehicule = false;
  Servo* myServo;
  virtual void tick() = 0;
};

// Declaration of the BarriereIn class inheriting from Barriere
class BarriereIn : public Barriere
{
public:
  BarriereIn(int* nbr);

  bool isThereAvehicule() override;
  void tick() override;
};

// Declaration of the BarriereOut class inheriting from Barriere
class BarriereOut : public Barriere
{
public:
  BarriereOut(int* nbr);

  bool isThereAvehicule() override;
  void tick() override;
};

// Forward declaration of the Parking class
class Parking;

// Declaration of the Afficheur class
class Afficheur
{
public:
  Parking* parking;
  //rgb_lcd lcd;
  Adafruit_RGBLCDShield lcd;

  Afficheur(Parking* p);

  void update();
  void print(int nbrPlacesLibres, const char* msg1, const char* msg2, const char* msg3, const char* msg4);
  const char* truncateString(const char* str, size_t maxLength);
};

// Declaration of the Vehicules class
class Vehicules
{
};

// Declaration of the Voiture class inheriting from Vehicules
class Voiture : public Vehicules
{
};

// Declaration of the Camion class inheriting from Vehicules
class Camion : public Vehicules
{
};

// Declaration of the Parking class
class Parking
{
private:
  Vehicules* vehicules[CAPACITY_MAX];

public:
  int nbrPlacesLibres;
  Barriere* barriere[2];
  Afficheur* afficheur;

  Parking();
  void tick();
};

#endif // PARKING_H
