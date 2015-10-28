/* Analog Input
 * Demonstrate analog input by reading A0 connected to
 * potentiometer. Vary time on/off at LED on pin 13 based on
 * value read at A0. * 
 */

int sensorPin = 0;
// LED Pin for flash and threshold (non-PWM)
//int ledPin = 13;
// LED Pin for fading requires PWM
int ledPin = 9;
int sensorValue = 0;

// For threshold sample
int threshold = 512;

// For knob/server sample
#include <Servo.h>
Servo myservo;

void setup() {
  pinMode(ledPin, OUTPUT);
  //myservo.attach(ledPin);
}

void loop() {
  // Flashing
  /*
  sensorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin, LOW);
  delay(sensorValue);
  */
  // Flashing

  // Threshold
  /*
  if (analogRead(sensorPin) > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  */
  // Threshold

  // Fading
  sensorValue = analogRead(sensorPin);
  if (sensorValue == 0) { sensorValue = 1; }
  analogWrite(ledPin, sensorValue / 4);
  // Fading

  // Knob Servo
  /*
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 180);
  myservo.write(sensorValue);
  delay(100);
  */
  // Knob Servo
}
