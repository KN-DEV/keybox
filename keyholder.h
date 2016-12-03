#pragma once
#include "Arduino.h"
#include "config.h"
#include <Button.h>
extern Button keyHolder;
void setupKeyHolder();
bool isKeyOnHolder();
void updateKeyBoxStatus();

