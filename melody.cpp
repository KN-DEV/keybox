#include "melody.h"
#include "state.h"
#include "noise.h"
Note ERROR_MELODY[] = {Note::_C3};
int ERROR_DURATION[] = {1}; 
Note WAITING_FOR_CLOSE_MELODY[] = {Note::_B0,Note::_DS8};
int WAITING_FOR_CLOSE_NOTE_DURATION[] = {4,4};
Note OPEN_MELODY[] = {Note::_C6};
int OPEN_DURATION[] = {8};
Note CLOSED_MELODY[] = {Note::_C6, Note::_C5, Note::_C6};
int CLOSED_DURATION [] = {4,4,4};
Note melody[] = {  Note::_C4};
//// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4};
void playMelody(State type) {
  switch (getState()) {
      case State::ERROR:
        playTones(ERROR_MELODY, ERROR_DURATION,1);
        return;
      case State::WAITING_FOR_CLOSE:
        playTones(WAITING_FOR_CLOSE_MELODY, WAITING_FOR_CLOSE_NOTE_DURATION,2);
        return;
      case State::OPEN:
        playTones(OPEN_MELODY, OPEN_DURATION,1);
        return;
      case State::CONTROL:
        playTones(melody, noteDurations,1);
        return;
      case State::CLOSED:
        playTones(CLOSED_MELODY, CLOSED_DURATION, 3);
        return;
    //case State::REJECT:
//        playTones(ERROR_MELODY, ERROR_DURATION);
//        return;
//      case State::OPENING:
//        playTones(melody, noteDurations);
//        return;
//    case State::IDLE:
//      return;
//    case State::ADD_CARD:
//      return;
//    case State::RESET:
//      return;
//    case State::LOCKED:
//      return;
//    case State::WAITING_FOR_OPEN:
//      return;
  }
}
