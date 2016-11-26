#include "door.h"
/**
   sprawdza stan drzwi
*/
bool doorStatus() {
    return digitalRead(DOOR_PIN);
};

/**
   sprawdza czy zeskanowana karta jest kartą RESET
*/
void unlockDoor() {
    digitalWrite(RELAY_PIN, LOW);
    delay(50);
    digitalWrite(RELAY_PIN, HIGH);
};

void setUpDoor() {
    pinMode(DOOR_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
}

