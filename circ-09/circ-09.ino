/*
 * Change intesity of LED based on amount of light indicated
 * by photo resistor.
 */

int lightPin = 0;
int lightLevel = 0;
int ledPin = 9;

int threshold = 300;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // LED diming according to photo resistor
  /*
  lightLevel = analogRead(lightPin);
  lightLevel = map(lightLevel, 0, 900, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
  // Dim under bright light, bright under low light
  analogWrite(ledPin, lightLevel);
  // Bright under bright light, dim under dim light
  //analogWrite(ledPin, 255 - lightLevel);
  */
  // LED diming according to photo resistor

  // Night light, threshold
  if (analogRead(lightPin) > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  // Night light, threshold
}
