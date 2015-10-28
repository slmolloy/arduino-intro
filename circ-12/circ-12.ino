/*
 * Control a multi color LED
 */

#define FADE_SPEED 10
#define CHANGE_DELAY 100

// The pins used to control RGB
// Red = 9, Green = 10, Blue = 11
int ledDigitalOne[] = {9, 10, 11};

const boolean ON = LOW;
const boolean OFF = HIGH;

// Defined colors {RED, GREEN, BLUE}
const byte RED[] = {255, 0, 0};
const byte ORANGE[] = {83, 4, 0};
const byte YELLOW[] = {255, 255, 0};
const byte GREEN[] = {0, 255, 0};
const byte BLUE[] = {0, 0, 255};
const byte INDIGO[] = {4, 0, 19};
const byte VIOLET[] = {23, 0, 22};
const byte CYAN[] = {0, 255, 255};
const byte MAGENTA[] = {255, 0, 255};
const byte WHITE[] = {255, 255, 255};
const byte BLACK[] = {0, 0, 0};
const byte PINK[] = {158, 4, 79};

const byte* COLORS[] = {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, CYAN, MAGENTA, WHITE, BLACK, PINK};

int randInt = 0;
int randIntLast = 0;
byte currentColor[] = {0, 0, 0};
byte newColor[] = {0, 0, 0};


void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledDigitalOne[i], OUTPUT);
  }
  copyColor(WHITE, currentColor);
  setColor(ledDigitalOne, currentColor);
  delay(CHANGE_DELAY);
}

void loop() {
  randomColor(newColor);
  fadeColor(ledDigitalOne, currentColor, newColor, FADE_SPEED);
  copyColor(newColor, currentColor);
  delay(CHANGE_DELAY);
}

void copyColor(byte* from, byte* to) {
  for (int i = 0; i < 3; i++) {
    to[i] = from[i];
  }
}

void copyColor(const byte* from, byte* to) {
  for (int i = 0; i < 3; i++) {
    to[i] = from[i];
  }
}

void setColor(int* led, byte* color) {
  for (int i = 0; i < 3; i++) {
    analogWrite(led[i], 255 - color[i]);
  }
}

void randomColor(byte* newColor) {
  while (randInt == randIntLast) {
    randInt = random(0, sizeof(COLORS) / 2);
  }
  randIntLast = randInt;
  copyColor(COLORS[randInt], newColor);
}

void fadeColor(int* led, byte* start, byte* final, int fade) {
  int cR = final[0] - start[0];
  int cG = final[1] - start[1];
  int cB = final[2] - start[2];
  int steps = max(abs(cR),max(abs(cG), abs(cB)));

  byte tC[3];
  for (int i = 0; i < steps; i++) {
    tC[0] = start[0] + (i * cR / steps);
    tC[1] = start[1] + (i * cG / steps);
    tC[2] = start[2] + (i * cB / steps);
    setColor(led, tC);
    delay(fade);
  }
  setColor(led, final);
}

