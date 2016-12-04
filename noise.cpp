#include "noise.h"
#include "nonBlockingDelay.h"
float getPauseBetweenNotes(int duration) {
  return  duration * 1.30;
}
void playTone(int note, int duration) {
  duration = 1000 / duration;
  tone(BUZZER_PIN, note, duration);
  nonBlockingDealy(getPauseBetweenNotes(duration));
  noTone(BUZZER_PIN);
}
void playTones(Note* tones, int* durations, int length) {
  for (int thisNote = 0; thisNote < length; thisNote++) {
    playTone( (int) tones[thisNote], durations[thisNote]);
  }
  noTone(BUZZER_PIN);
}
