#define DATA 2
#define CLOCK 3
#define LATCH 4

int ledState = 0;
#define ON HIGH
#define OFF LOW

int x = 1;
int i = 0;
int j = 7;

void setup()
{
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
}

/*
void loop()
{
  int delayTime = 1;
  
  for(int i = 0; i < 256; i++) {
    //updateLEDs(i);
    updateLEDsLong(i);
    delay(delayTime);
  }
}
*/

void loop()
{
  int delayTime = 100;
  
  changeLED(i, ON);
  changeLED(j, ON);
  delay(delayTime);
  changeLED(i, OFF);
  changeLED(j, OFF);
  delay(delayTime);
  
  if ((j - i) > 0) {
    i = i + x;
    j = j - x;
  }
  
  if ((j - i) < 1 || i == 0 || j == 7) {
    x = x * -1;
    i = i + x;
    j = j - x;
  }
}

void updateLEDs(int value)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, value);
  digitalWrite(LATCH, HIGH);
}

void updateLEDsLong(int value)
{
  int b = 0;
  int i = 0;
  // Pull chips latch low
  digitalWrite(LATCH, LOW);
  
  for(i = 0; i < 8; i++) {
    // Use bitmask to select only the eighth
    // bit in our number
    b = value & B10000000;

    // Move number up one bit value
    value = value << 1;
    
    if (b == 128) {
      // If bit 8 is set then set data pin high
      digitalWrite(DATA, HIGH);
    } else {
      // Else if 8 bit is unset then set data pin low
      digitalWrite(DATA, LOW);
    }

    // Next 3 lines pulse the clock pin    
    digitalWrite(CLOCK, HIGH);
    delay(1);
    digitalWrite(CLOCK, LOW);
  }
  
  // Pull latch high shifting our data to being displayed
  digitalWrite(LATCH, HIGH);
}

int bits[]  = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};
int masks[] = {B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111};

void changeLED(int led, int state)
{
  ledState = ledState & masks[led];
  if (state == ON) {
    ledState = ledState | bits[led];
  }
  updateLEDs(ledState);
}
