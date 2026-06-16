// Vars
const int pinArray[] = {12, 11, 10, 8, 7, 5, 3, 2};
  int current = 0;
  int direction = 1;

void setup() {
  // Output sturen naar alle aangesloten pins
  for (int i = 0; i < 8; i++) {
    pinMode(pinArray[i], OUTPUT);
  }
}

void loop() {
  // Eerst alle leds uitzetten aan het begin
  for (int i = 0; i < 8; i++) {
    digitalWrite(pinArray[i], LOW);
  }

  // Aanzetten van de eerste pin op volgorde van current en direction
  digitalWrite(pinArray[current], HIGH);
  delay(100);

  // Doorgaan naar de volgende
  current += direction;

  // Veranderen van richting aan het einde
  if (current == 7) {
    direction = -1;
  } else if (current == 0) {
    direction = 1;
  }
}
