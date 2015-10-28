int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int ledCount = 8;

int ledOnTime = 60;
int ledOffTime = 0;
int pinStep = 1;
int pinIndex = 0;

void setup()
{
  for(int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  oneAfterAnotherNoLoop();
  //backAndForth();
}

void oneAfterAnotherNoLoop()
{
  for(int i = 0; i < ledCount; i++) {
    lightSwitch(ledPins[i]);
  }
}

void backAndForth()
{
  while(pinIndex >= 0 && pinIndex <= (ledCount - 1)) {
    lightSwitch(ledPins[pinIndex]);
    pinIndex += pinStep;
  }
  pinStep = pinStep * -1;
  pinIndex += (2 * pinStep);
}

void lightSwitch(int pin)
{
  digitalWrite(pin, HIGH);
  delay(ledOnTime);
  digitalWrite(pin, LOW);
  delay(ledOffTime); 
}
