#include "lock.h"
#include "config.h"
#include "nonBlockingDelay.h"
Button lockSensor(LOCK_SENSOR_PIN);
bool isLockOpened() {
    return lockSensor.read() == Button::PRESSED;
};
void unlockLock() {
    digitalWrite(LOCK_PIN, LOW);
    nonBlockingDealy(LOCK_DELAY);
    digitalWrite(LOCK_PIN, HIGH);
};
void setupLock() {
    pinMode(LOCK_PIN, OUTPUT);
    digitalWrite(LOCK_PIN, HIGH);
}
void setupLockSensor() {
    lockSensor.begin();
}
