#include "keyholder.h"
Button keyHolder(KEY_HOLDER_PIN);
void setupKeyHolder() {
  keyHolder.begin();
  pinMode(KEYBOX_STATUS_PIN, OUTPUT);
}
bool isKeyOnHolder() {
  return keyHolder.pressed();
}
void updateKeyBoxStatus() {
  digitalWrite(KEYBOX_STATUS_PIN, isKeyOnHolder());
}
