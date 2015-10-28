/* Melody
 * (cleft) 2005 D. Cuartielles for K3
 *
 * This example uses a piezo speaker to play melodies.  It sends
 * a square wave of the appropriate frequency to the piezo, generating
 * the corresponding tone.
 *
 * The calculation of the tones is made following the mathematical
 * operation:
 *
 *       timeHigh = period / 2 = 1 / (2 * toneFrequency)
 *
 * where the different tones are described as in the table:
 *
 * note 	frequency 	period 	timeHigh
 * c 	        261 Hz 	        3830 	1915 	
 * d 	        294 Hz 	        3400 	1700 	
 * e 	        329 Hz 	        3038 	1519 	
 * f 	        349 Hz 	        2864 	1432 	
 * g 	        392 Hz 	        2550 	1275 	
 * a 	        440 Hz 	        2272 	1136 	
 * b 	        493 Hz 	        2028	1014	
 * C	        523 Hz	        1912 	956
 *
 * http://www.arduino.cc/en/Tutorial/Melody
 */
  
int speakerPin = 9;

char names[] = { ' ', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 't' };
int tones[] = { 0, 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 1 };


struct song_t {
  int length;
  char notes[128];
  int beats[128];
  int tones[128];
};

typedef struct song_t song;

song *s = NULL;
song test =     {18, "cdefgabC Cbagfedc ", {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
song twinkle =  {15, "ccggaagffeeddc ",    {1,1,1,1,1,1,2,1,1,1,1,1,1,2,4}};
song birthday = {13, "ccdcfeccdcgf",       {1,1,1,1,1,2,1,1,1,1,1,2,4}};
song high =     {5,  "ttttt",              {1,2,3,4,5}};

int length = 18; // the number of notes
char notes[] = "cdefgabC Cbagfedc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

//int length = 15; // the number of notes
//char notes[] = "ccggaagffeeddc "; // a space represents a rest
//int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 250;
int rest = tempo / 4;

void playTone(int tone, int duration)
{
  if (tone == 0) {
    delay(duration);
    return; 
  }
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration)
{
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void preProcess(struct song_t *s)
{
  for (int i = 0; i < s->length; i++) {
     switch (s->notes[i]) {
     case ' ': s->tones[i] = tones[0]; break;
     case 'c': s->tones[i] = tones[1]; break;
     case 'd': s->tones[i] = tones[2]; break;
     case 'e': s->tones[i] = tones[3]; break;
     case 'f': s->tones[i] = tones[4]; break;
     case 'g': s->tones[i] = tones[5]; break;
     case 'a': s->tones[i] = tones[6]; break;
     case 'b': s->tones[i] = tones[7]; break;
     case 'C': s->tones[i] = tones[8]; break;
     case 't': s->tones[i] = tones[9]; break;
     default: break;     
     }
  }
}

void playSong(struct song_t *s)
{
  for (int i = 0; i < s->length; i++) {
    playTone(s->tones[i], s->beats[i] * tempo);
    delay(rest);
  } 
}

void setup()
{
  pinMode(speakerPin, OUTPUT);
  s = &birthday;
}

void loop()
{
  preProcess(s);
  playSong(s);
  
  
  for (int i = 0; i < s->length; i++) {
    if (s->notes[i] == ' ') {
      delay(s->beats[i] * tempo); // rest
    } else {
      playNote(s->notes[i], s->beats[i] * tempo);
    }
    // pause between notes
    delay(rest); 
  }
  
}
