#ifndef NOISE_H
#define NOISE_H
#include "Arduino.h"
#include "config.h"
#include "pitches.h"
#include "state.h"

void playMelody(int* tones, int* durations);
void makeNoise(State type);
extern int melody[];
extern int noteDurations[];


extern int WAITING_FOR_CLOSE_MELODY[]; 

extern int WAITING_FOR_CLOSE_NOTE_DURATION[]; 
#endif
