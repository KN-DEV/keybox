#include "noise.h"//// notes in the melody:



float getPauseBetweenNotes(int duration) {
  return  duration * 1.30;
}

void playTone(int note, int duration) {
  duration = 1000 / duration;
  tone(BUZZER_PIN, note, duration);
  noBlockingDealy(getPauseBetweenNotes(duration));
  noTone(BUZZER_PIN);
}


void playTones(int* tones, int* durations) {
  for (int thisNote = 0; thisNote < sizeof(tones) / sizeof(int); thisNote++) {
    playTone( tones[thisNote], durations[thisNote]);
  }
}



