#include <Servo.h>

Servo servoMotor;

const int firstButtonPin = 12;
const int secondButtonPin = 7;
const int servoPin = 3;

int currentAngle = 0;

void moveServo(int forwardTime, int waitingTime, int backwardsTime) {
  int stepDelayForward = forwardTime / 120;
  int stepDelayBackwards = backwardsTime / 120;

  static int state = 0; // 0 = forwards, 1 = wait, 2 = backwards

  if (state == 0) {
  servoMotor.write(currentAngle);

  if (digitalRead(firstButtonPin) == HIGH) {
  state = 1;
  return;
}
  currentAngle++;
  delay(stepDelayForward);
}

  else if (state == 1) {
  delay(waitingTime);
  state = 2;
}

  else if (state == 2) {
  servoMotor.write(currentAngle);

  if (digitalRead(secondButtonPin) == HIGH) {
  state = 0;
  return;
}
  currentAngle--;
  delay(stepDelayBackwards);
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
