#ifndef LOCK_H
#define LOCK_H
#include "Arduino.h"
#include "config.h"
#include <Button.h>
extern Button lockSensor;
bool isLockOpened();
void unlockLock();
void setupLock();
void setupLockSensor();
#endif
