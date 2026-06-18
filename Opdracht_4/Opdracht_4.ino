// Alle pins die ik gebruik
const int pinArray[] = {13, 12, 9, 6, 3, 2};
// Aantal pins
const int pinAmount = 6;
// Analoge pot pin
const int potPin = A5;
// Potwaarde, beginnend met 0
int potValue = 0;

// Methode om alle pins ouput te geven
void giveAllPinsOutput() {
  for (int i = 0; i < 6; i++) {
    pinMode(pinArray[i], OUTPUT);
  }
}

// Method om de leds aan te doen met de rotatie
void turnOnLedsWithRotation(int value) {
  // Map maken met de value parameter de waardes van de potmeter zelf en het aantal pins
  int turnOn = map(value, 0, 1023, 0, pinAmount);
  for (int i = 0; i < 6; i++) {
    // Zet de pin aan als die nog niet aan staat
    if (i < turnOn) {
      digitalWrite(pinArray[i], HIGH);
    // Zet de pin uit als die aan staat
    } else {
      digitalWrite(pinArray[i], LOW);
    }
  }
}

// Setup
void setup() {
  giveAllPinsOutput();
}

// Loop
void loop() {
  // Potwaarde uitlezen van de analoge pin
  potValue = analogRead(potPin);
  // Potwaarde meegeven als parameter
  turnOnLedsWithRotation(potValue);
}
