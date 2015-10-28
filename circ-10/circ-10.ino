/*
 * Read temperature from sensor and write to debug console.
 */

int tempPin = 0;
float temp = 0.0;

void setup() {
  // Start serial connection with the computer
  Serial.begin(115200);
}

void loop() {
  temp = getVoltage(tempPin);
  temp = (temp - .5) * 100;
  Serial.print(temp);
  Serial.print("C = ");
  temp = temp * 1.8 + 32;
  Serial.print(temp);
  Serial.println("F");
  delay(1000);
}

float getVoltage(int pin) {
  return (analogRead(pin) * .004882814);
}

