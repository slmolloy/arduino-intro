#define DIGITAL_LED_PIN 13
#define ANALOG_LED_PIN 9
#define IN1_PIN 2
#define IN2_PIN 3
#define PIN_DELAY 50

enum run_mode {
  ON_OFF = 0,
  TOGGLE,
  FADE
};
enum run_mode mode = FADE;

void (*func)();

int pin1_val = HIGH;
int pin2_val = HIGH;
int led_val = LOW;
int led_analog = 0;
int pin1_cur = 0;
int pin2_cur = 0;
int pin1_delay = 0;
int pin2_delay = 0;

void switchLED(int pin)
{
  //int val = bitRead(PORTB, pin);
  int val = digitalRead(pin);
  if (val == 0) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

void onOffButtons()
{
  /*
   * Button 1 -- off
   * Button 2 -- on
   * Simple on/off button logic
   */
  if (digitalRead(IN1_PIN) == LOW) {
    digitalWrite(DIGITAL_LED_PIN, LOW); 
  } else if (digitalRead(IN2_PIN) == LOW) {
    digitalWrite(DIGITAL_LED_PIN, HIGH);
  }
}

void toggleButtons()
{
  /*
   * Button 1 & 2 -- toggle buttons
   * Pressing either button 1 or 2 will toggle the led
   * If conditions ensure button is released before next read to toggle switch
   * Delay is used so button cannot be double clicked too fast or smooths out glitches
   */
  if (((pin1_cur = digitalRead(IN1_PIN)) == LOW)
      && (pin1_cur != pin1_val)
      && (pin1_delay == 0)) {
    pin1_val = pin1_cur;
    pin1_delay = PIN_DELAY;
    switchLED(DIGITAL_LED_PIN);
  } else if (pin1_cur == HIGH) {
    pin1_val = HIGH;
  }
  
  if (((pin2_cur = digitalRead(IN2_PIN)) == LOW)
      && (pin2_cur != pin2_val)
      && (pin2_delay == 0)) {
    pin2_val = pin2_cur;
    pin2_delay = PIN_DELAY;
    switchLED(DIGITAL_LED_PIN);
  } else if (pin2_cur == HIGH) {
    pin2_val = HIGH; 
  }
  
  if (pin1_delay != 0) { pin1_delay--; }
  if (pin2_delay != 0) { pin2_delay--; }
  
  delay(1);
}

void fadeButtons()
{
  /*
   * Button 1 & 2 fade the LED up and down
   * Need to have the LED controlled by the ANALOG_LED_PIN
   */
  if (digitalRead(IN1_PIN) == LOW) { led_analog--; }
  else if (digitalRead(IN2_PIN) == LOW) { led_analog++; }
  led_analog = constrain(led_analog, 0, 255);
  analogWrite(ANALOG_LED_PIN, led_analog);
  delay(60);
}

void setup()
{
  pinMode(DIGITAL_LED_PIN, OUTPUT);
  digitalWrite(DIGITAL_LED_PIN, led_val);
  pinMode(ANALOG_LED_PIN, OUTPUT);
  pinMode(IN1_PIN, INPUT);
  pinMode(IN2_PIN, INPUT);
  
  switch(mode) {
  case 0:
    func = &onOffButtons;
    break;
  case 1:
    func = &toggleButtons;
    break;
  case 2:
    func = &fadeButtons;
    break;
  default:
    func = NULL;
    break;
  }
}

void loop()
{
  if (func != NULL) {
    func();
  } else {
    delay(1000); 
  }
}
