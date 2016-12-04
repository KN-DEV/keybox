#pragma once
#include "Arduino.h"
#include <Button.h>
extern Button lockSensor;
bool isLockOpened();
void unlockLock();
void setupLock();
void setupLockSensor();
