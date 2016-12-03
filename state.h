#pragma once
#include "Arduino.h"
#include "config.h"
#include "melody.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


static const char* StateLabel[] = {
  "IDLE",
  "OPENING",
  "WAITING_FOR_OPEN",
  "ERROR",
  "OPEN",
  "WAITING_FOR_CLOSE",
  "CLOSED",
  "CONTROL",
  "REJECT",
  "ADD_CARD",
  "RESET",
  "LOCKED"
};
extern LiquidCrystal_I2C lcd;
extern State state;
void setupState();
State getState();
void setState(State s);
const char * getTextForEnum( int enumVal );

