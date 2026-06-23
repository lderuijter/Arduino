void setup() {
  // output geven aan de pins die gebruikt worden
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // led 11 uit, 13 aan
  digitalWrite(11, LOW);
  digitalWrite(13, HIGH);
  // 2 seconden wachten
  delay(2000);

  // led 13 uit, 11 aan
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  // 2 seconden wachten
  delay(2000);
}