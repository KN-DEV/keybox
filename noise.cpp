#include "noise.h"//// notes in the melody:

int melody[] = {
  NOTE_C4
};
//
//// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4
};


extern int WAITING_FOR_CLOSE_MELODY[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

extern int WAITING_FOR_CLOSE_NOTE_DURATION[] = {
  4
};



float getPauseBetweenNotes(int duration) {
 return  duration * 1.30;
}

void playTone(int note, int duration) {
  duration = 1000 / duration;
  tone(BUZZER_PIN, note, duration);
  delay(getPauseBetweenNotes(duration));
  noTone(BUZZER_PIN);
}


void playMelody(int* tones, int* durations){
    for (int thisNote = 0; thisNote < sizeof(tones)/sizeof(int); thisNote++) {
    playTone( tones[thisNote], durations[thisNote]);
  }
}
void makeNoise(State type) {


  switch (type) {
    case State::WAITING_FOR_CLOSE:
playMelody(melody,noteDurations);
      break;
  }
  

}


