#pragma once
#include "Arduino.h"
#include "config.h"
#include "nonBlockingDelay.h"
#include <Button.h>
extern Button lockSensor;
bool isLockOpened();
void unlockLock();
void setupLock();
void setupLockSensor();

