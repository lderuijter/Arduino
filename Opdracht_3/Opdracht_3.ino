// Vars van welke ports er gebruikt worden
const int button = 8;
const int light_1 = 5;
const int light_2 = 11;

// Teller om de clicks bij te houden
int counter = 0;

// Knop status van vorige zet onthouden
bool previousButtonState = HIGH;

void setup() {
  // Stroom geven aan alle componenten
  pinMode(button, INPUT_PULLUP);
  pinMode(light_1, OUTPUT);
  pinMode(light_2, OUTPUT);
}

void loop() {
  // Huidige status van de knop uitlezen
  bool currentButtonState = digitalRead(button);

  // if statement voor wanneer de knop wordt ingedrukt
  // komt altijd van HIGH af en gaat naar LOW
  if (previousButtonState == HIGH && currentButtonState == LOW) {
    // Druk op de knop, dus teller optellen
  	counter++;
    
    // Methode aanroepen voor de led lichten
    lightLogic();
    
    // debounce
    delay(50);
  }
  
  // Methode aanroepen om de status van de knop te updaten
  updateButtonState(currentButtonState);
}

void lightLogic() {
  // Om en om de lampen aan en uit zetten
  // Regel: 1 gaat aan 2 uit, 2 gaat aan 1 uit
  if (counter % 2 == 0) {
    digitalWrite(light_1, HIGH);
    digitalWrite(light_2, LOW);
  } else {
    digitalWrite(light_1, LOW);
    digitalWrite(light_2, HIGH);
  }
}

void updateButtonState(bool currentState) {
  // Knop status updaten met wat het als laatste was zodat de loop weer opniew kan beginnen
  previousButtonState = currentState;
}
