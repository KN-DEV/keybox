#ifndef KEYHOLDER_H
#define KEYHOLDER_H
#include "Arduino.h"
#include "config.h"
#include <Button.h>
extern Button keyHolder;
void setupKeyHolder();
bool isKeyOnHolder();
void updateKeyBoxStatus();
#endif
