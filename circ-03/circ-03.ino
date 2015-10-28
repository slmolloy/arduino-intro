int motorPin = 9;

void setup()
{
  pinMode(motorPin, OUTPUT); 
}

void loop()
{
  //motorOnThenOff();
  //motorOnThenOffWithSpeed();
  motorAcceleration();
}

void motorOnThenOff()
{
  int onTime = 2500;
  int offTime = 1000;
  
  digitalWrite(motorPin, HIGH);
  delay(onTime);
  digitalWrite(motorPin, LOW);
  delay(offTime);
}

void motorOnThenOffWithSpeed()
{
  int onSpeed = 200;
  int onTime = 2500;
  int offSpeed = 80;
  int offTime = 25000;
  
  analogWrite(motorPin, onSpeed);
  delay(onTime);
  analogWrite(motorPin, offSpeed);
  delay(offTime);
}

void motorAcceleration()
{
  int delayTime = 40;
  
  for(int i = 100; i < 256; i++) {
    analogWrite(motorPin, i);
    delay(delayTime);
  }
  for(int i = 255; i >= 100; i--) {
    analogWrite(motorPin, i);
    delay(delayTime);
  }
}


