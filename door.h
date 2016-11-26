#ifndef DOOR_H
#define DOOR_H
#include "Arduino.h"
#include "config.h"

/**
   sprawdza stan drzwi
*/
bool doorStatus();
/**
   sprawdza czy zeskanowana karta jest kartą RESET
*/
void unlockDoor();

void setUpDoor();
#endif
