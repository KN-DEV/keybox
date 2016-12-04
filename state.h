#pragma once
#include "Arduino.h"
#include "config.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;
extern State state;
void setupState();
State getState();
void setState(State s);
const char * getTextForEnum( int enumVal );
