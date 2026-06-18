#include <Servo.h>

Servo servoMotor;

const int firstButtonPin = 12;
const int secondButtonPin = 7;
const int servoPin = 3;

int currentAngle = 0;
const int debounce = 2;

enum Direction { FORWARD, BACKWARD };
Direction dir = FORWARD;

void moveServo(int forwardTime, int waitingTime, int backwardsTime) {
  int stepDelayForward = forwardTime / 120;
  int stepDelayBackwards = backwardsTime / 120;

  if (dir == FORWARD) {
    currentAngle++;
    if (currentAngle >= 120) {
      delay(waitingTime);
      dir = BACKWARD;
    }
    delay(stepDelayForward);
  }

  else {
    currentAngle--;
    if (currentAngle <= 0) {
      dir = FORWARD;
    }
    delay(stepDelayBackwards);
  }
  servoMotor.write(currentAngle);
  delay(debounce);

  if (digitalRead(firstButtonPin) == HIGH || digitalRead(secondButtonPin) == HIGH) {
    return;
  }
}

void setup() {
  pinMode(firstButtonPin, INPUT_PULLUP);
  pinMode(secondButtonPin, INPUT_PULLUP);

  servoMotor.attach(servoPin);
  servoMotor.write(0);
}

void loop() {
  bool firstButton = digitalRead(firstButtonPin) == LOW;
  bool secondButton = digitalRead(secondButtonPin) == LOW;

  if (firstButton && secondButton) {
    moveServo(3000, 5000, 500);
  }
  else if (firstButton) {
    moveServo(3000, 0, 3000);
  }
  else if (secondButton) {
    moveServo(500, 0, 500);
  }
}
