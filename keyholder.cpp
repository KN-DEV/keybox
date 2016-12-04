#include "keyholder.h"
#include "config.h"
Button keyHolder(KEY_HOLDER_PIN);
void setupKeyHolder() {
  keyHolder.begin();
  pinMode(KEYBOX_STATUS_PIN, OUTPUT);
}
bool isKeyOnHolder() {
    return keyHolder.read() == Button::PRESSED;
}
void updateKeyBoxStatus() {
  digitalWrite(KEYBOX_STATUS_PIN, isKeyOnHolder());
}

