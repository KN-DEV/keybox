#pragma once
#include "Arduino.h"
#include "config.h"
#include "pitches.h"
#include "nonBlockingDelay.h"

void playTones(int* tones, int* durations);


extern int WAITING_FOR_CLOSE_MELODY[]; 

extern int WAITING_FOR_CLOSE_NOTE_DURATION[]; 

