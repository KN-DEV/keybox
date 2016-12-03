#include "melody.h"


int melody[] = {
  NOTE_C4
};
//
//// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4
};


int WAITING_FOR_CLOSE_MELODY[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int WAITING_FOR_CLOSE_NOTE_DURATION[] = {
  4
};


void playMelody(State type) {
  switch (getState()) {
    case State::IDLE:
      return;
    case State::REJECT:
      return;
    case State::CONTROL:
      playTones(melody, noteDurations);
      return;
    case State::ADD_CARD:
      playTones(melody, noteDurations);
      return;
    case State::RESET:
      playTones(melody, noteDurations);
      return;
    case State::LOCKED:
      playTones(melody, noteDurations);
      return;
    case State::OPENING:
      return;
    case State::WAITING_FOR_OPEN:
      return;
    case State::OPEN:
      return;
    case State::ERROR:
      playTones(melody, noteDurations);
      return;
    case State::WAITING_FOR_CLOSE:
      playTones(melody, noteDurations);
      return;
    case State::CLOSED:
      return;
  }
}
