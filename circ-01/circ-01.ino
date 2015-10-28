int ledPin = 9;
int maxAnalog = 180;
int minAnalog = 0;
int analogStep = 5;
int dimSpeed = 70;
int pauseTime = 3000;

void setup() {
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  //digitalWrite(ledPin, HIGH);
  //delay(1000);
  //digitalWrite(ledPin, LOW);
  //delay(1000);
  int i = 0;
  for(i = minAnalog; i < maxAnalog; i+=analogStep) {
    analogWrite(ledPin, i);
    delay(dimSpeed);
  }
  for(i = maxAnalog; i > minAnalog; i-=analogStep) {
    analogWrite(ledPin, i);
    delay(dimSpeed);
  }
  delay(pauseTime);
}


