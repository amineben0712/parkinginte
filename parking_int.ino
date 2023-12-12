#include "parking_int.h"
//#include "rgb_lcd.h"
#include <Adafruit_RGBLCDShield.h>

// Implementation of the Capteur class

Capteur::Capteur(int tPin, int ePin)
  : trigPin(tPin), echoPin(ePin) {
  pinMode(tPin, OUTPUT);
  pinMode(ePin, INPUT);
}

bool Capteur::getStatus() {
  // Set trigger pin low for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigger pin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters using the speed of sound
  distanceCm = duration * SOUND_VELOCITY / 2;

  // Check if distance is less than or equal to 10.0 cm
  if (distanceCm <= 10.0) {
    return true;
  } else {
    return false;
  }
}

// Implementation of the BarriereIn class

BarriereIn::BarriereIn(int* nbr) {
  // Initialize Capteur instance with specific pins
  capteur = new Capteur(D6, D5);
  myServo = new Servo;
  myServo->attach(D3);
  nbrPlacesLibres = nbr;
}

bool BarriereIn::isThereAvehicule() {
  return capteur->getStatus();
}

void BarriereIn::tick(void) {
  // Check for the presence of a vehicle
  isThereAvehicule();
  if (isThereAvehicule() == true) {
    if ((*nbrPlacesLibres) > 0) {
      if (servirVehicule == false) {
        // Raise the servo arm if a vehicle is detected and there are available parking spaces
        servirVehicule = true;
        myServo->write(180);
        (*nbrPlacesLibres)--;
      }
    }
  } else {
    // Lower the servo arm if no vehicle is detected
    servirVehicule = false;
    myServo->write(0);
  }
}

// Implementation of the BarriereOut class

BarriereOut::BarriereOut(int* nbr) {
  // Initialize Capteur instance with specific pins
  capteur = new Capteur(D4, D8);
  myServo = new Servo;
  myServo->attach(D7);
  nbrPlacesLibres = nbr;
}

bool BarriereOut::isThereAvehicule() {
  return capteur->getStatus();
}

void BarriereOut::tick() {
  // Check for the presence of a vehicle
  isThereAvehicule();
  if (isThereAvehicule() == true) {
    if ((*nbrPlacesLibres) < CAPACITY_MAX) {
      if (servirVehicule == false) {
        // Raise the servo arm if a vehicle is detected and there are available parking spaces
        servirVehicule = true;
        myServo->write(180);
        (*nbrPlacesLibres)++;
      }
    }
  } else {
    // Lower the servo arm if no vehicle is detected
    servirVehicule = false;
    myServo->write(0);
  }
}

// Implementation of the Afficheur class

Afficheur::Afficheur(Parking* p) {
  parking = p;
}

void Afficheur::update() {
  if (parking->nbrPlacesLibres > 0) {
    // Display the number of available parking spaces and a welcome message
    print(parking->nbrPlacesLibres, "", "", "     Welcome", "");
  } else {
    if (parking->barriere[0]->servirVehicule == false) {
      // Display a message to come back later if no parking spaces are available
      print(0, "", "Merci de", "revenir", "Come back later");
    } else {
      // Display the number of available parking spaces and a welcome message
      print(parking->nbrPlacesLibres, "", "", "     Welcome", "");
    }
  }
}

void Afficheur::print(int nbrPlacesLibres, const char* msg1, const char* msg2, const char* msg3, const char* msg4) {
  char buffer[17];  // Maximum length of a line on a 16x2 display

  lcd.clear();  // Clear the display

  // Display the number of available parking spaces
  snprintf(buffer, sizeof(buffer), "    %d places", nbrPlacesLibres);
  lcd.setCursor(0, 0);
  lcd.print(buffer);

  // Display the following messages on the next lines, truncating if necessary
  lcd.setCursor(0, 1);
  lcd.print(truncateString(msg1, 16));
  lcd.setCursor(0, 2);
  lcd.print(truncateString(msg2, 16));
  lcd.setCursor(0, 3);
  lcd.print(truncateString(msg3, 16));
  lcd.setCursor(0, 4);
  lcd.print(truncateString(msg4, 16));
}

// Utility function to truncate a string if it exceeds a certain length
const char* Afficheur::truncateString(const char* str, size_t maxLength) {
  static char truncated[17];  // Maximum length of a line on a 16x2 display

  strncpy(truncated, str, maxLength);
  truncated[maxLength] = '\0';

  return truncated;
}

// Implementation of the Parking class

Parking::Parking() {
  // Use exceptions
  if (CAPACITY_MAX < 0) throw 1;
  nbrPlacesLibres = CAPACITY_MAX;
  barriere[B_IN] = new BarriereIn(&nbrPlacesLibres);
  barriere[B_OUT] = new BarriereOut(&nbrPlacesLibres);
  afficheur = new Afficheur(this);
}

void Parking::tick() {
  // Process both barriers
  barriere[B_IN]->tick();
  barriere[B_OUT]->tick();

  // Update display based on barrier states
  if (barriere[B_IN]->servirVehicule == true || barriere[B_OUT]->servirVehicule == true) {
    afficheur->print(nbrPlacesLibres, "", "", "     Welcome", "");
  } else {
    if (nbrPlacesLibres > 0) {
      afficheur->print(nbrPlacesLibres, "", "", "     Welcome", "");
    } else {
      afficheur->print(0, "", "", "", "Come back later");
      afficheur->update();
    }
  }

  afficheur->update();
}

// Redefinition of operator
/*class Servo {
   Servo & operator ++(int){
      myServo->write(180);
          return(*this);}
  Servo & operator --(int){
      myServo->write(0);
  return(*this);}
}*/
Parking* parking;
//Afficheur* afficheur;
Afficheur* afficheur;

Adafruit_RGBLCDShield lcd;
void setup() {
  /*Serial.begin(9600);
  Serial.printf("Bonjour\n");
  Serial.printf("Bonjour\n");
  lcd.begin(16, 2);*/
  parking = new Parking;
}
void loop() {

  try {
    parking->tick();
  } catch (int erreur) {
    if (erreur == 1) {
      afficheur->print(0, "Erreur capacité max", "", "", "");

    } else {
      afficheur->print(0, "Exception inconnue", "", "", "");
    }
  }
}