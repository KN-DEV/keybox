#ifndef NOISE_H
#define NOISE_H
#include "Arduino.h"
#include "config.h"
#include "pitches.h"

enum class Noise {
  ACCESS_GRANTED,
  ACCESS_DENIED 
};
void makeNoise(int type);
extern int melody[1][8];
extern int noteDurations[1][8];
#endif
