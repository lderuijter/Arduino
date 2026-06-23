#include <Servo.h>

// ServoMotor object aanmaken
Servo servoMotor;

// Pins vaststellen
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 3;

// Variabele voor het opslaan van de hoek
int angle;

// Methode om de afstand te meten met de sensor
float getCurrentDistance() {
  // triggerpuls om te starten met meten
  digitalWrite(trigPin, LOW);
  delay(2);

  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // meet de reistijd van het geluid
  long duration = pulseIn(echoPin, HIGH, 20000);

  // zet de tijd om naar afstand in centimeters
  return duration * 0.0343 / 2;
}

// Methode om de afstand toe te wijzen aan een hoek en die op de servo toepassen
void writeAngles(float currentDistance) {
  // object verder dan 10cm dus rusten op 0 graden
  if (currentDistance >= 10) {
    angle = 0;
  }
  // object dichterbij dan 4cm dus 180 graden
  else if (currentDistance <= 4) {
    angle = 180;
  }
  // object tussen de 4 en 10cm dus hoek bepalen met een map
  else {
    angle = map(currentDistance, 10, 4, 0, 180);
  }
  // berekende hoek toepassen op de servo
  servoMotor.write(angle);
}

void setup() {
  // sensor pinnen op input en output zetten
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo motor vastzetten en beginnen op 0
  servoMotor.attach(servoPin);
  servoMotor.write(0);
}

void loop() {
  // geef de afstand mee als parameter om de hoek te berekenen en toe te passen
  writeAngles(getCurrentDistance());
}
