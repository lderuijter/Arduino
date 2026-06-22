#include <Servo.h>

// ServoMotor object aanmaken
Servo servoMotor;

// Alle pins vaststellen
const int firstButtonPin = 12;
const int secondButtonPin = 7;
const int servoPin = 3;

// Hoek op 0 beginnen met een keine debounce
int currentAngle = 0;
const int debounce = 2;

// Direction enum aanmaken voor naar voren en terug
enum Direction { FORWARD, BACKWARD };
Direction dir = FORWARD;

// moveServo methode met de tijden als parameters
void moveServo(int forwardTime, int waitingTime, int backwardsTime) {
  // stepDelay voor naar voren en terug
  int stepDelayForward = forwardTime / 120;
  int stepDelayBackwards = backwardsTime / 120;

  // als naar voren dan ++
  if (dir == FORWARD) {
    currentAngle++;
    // gelijk aan of verder dan 120 graden dan wachten (als die een tijd heeft)
    // daarna richting aanpassen naar terug
    if (currentAngle >= 120) {
      delay(waitingTime);
      dir = BACKWARD;
    }
    // Snelheid toepassen om naar voren te gaan
    delay(stepDelayForward);
  }

  // Niet naar voren is naar achteren, dus --
  else {
    currentAngle--;
    // hoek op 0 of minder dan richting veranderen meteen
    if (currentAngle <= 0) {
      dir = FORWARD;
    }
    // Snelheid toepassen om weer terug te gaan
    delay(stepDelayBackwards);
  }
  // Angle blijven updaten met een debounce
  servoMotor.write(currentAngle);
  delay(debounce);

  // Als er niks wordt ingedrukt dan return (dus stoppen)
  if (digitalRead(firstButtonPin) == HIGH || digitalRead(secondButtonPin) == HIGH) {
    return;
  }
}

// Setup, pins toepassen op knoppen
void setup() {
  pinMode(firstButtonPin, INPUT_PULLUP);
  pinMode(secondButtonPin, INPUT_PULLUP);

  // Servo motor vastzetten en beginnen op 0
  servoMotor.attach(servoPin);
  servoMotor.write(0);
}

// Loop, logica voor het indrukken van de knoppen
void loop() {
  // uitlezen of de eerste en tweede knop ingedrukt zijn met een check is gelijk aan LOW
  bool firstButton = digitalRead(firstButtonPin) == LOW;
  bool secondButton = digitalRead(secondButtonPin) == LOW;

  // allebei, dan 3 seconden heen, 5 seconden wachten, 0,5 seconden terug
  if (firstButton && secondButton) {
    moveServo(3000, 5000, 500);
  }
  // alleen de eerste knop dus 3 seconden heen en 3 seconden terug
  else if (firstButton) {
    moveServo(3000, 0, 3000);
  }
  // alleen de tweede knop dus 0,5 seconden heen en 0,5 seconden terug
  else if (secondButton) {
    moveServo(500, 0, 500);
  }
}
