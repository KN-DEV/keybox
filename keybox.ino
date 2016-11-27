#include "Arduino.h"
#include "state.h"
#include "pitches.h"
#include "card.h"
#include "database.h"
#include "lock.h"
#include "noise.h"
#include "keyholder.h"
#include "config.h"
void setup() {
  setupKeyHolder();
  setupLockSensor();
  setupLock();
  setupState();
  setupRFID();
  setupDatabase();
};

#define CONTROL_TIMEOUT 5000
#define WAITING_FOR_CLOSE_TIMEOUT 10000
unsigned long long  stoper = 0;
void loop() {

  updateKeyBoxStatus();

  switch (getState()) {
    case State::IDLE:
      if (!isCardScaned()) {
        return;
      }
      switch (checkCard(cardUID)) {
        case Card::MASTER:
          setState(State::CONTROL);
          stoper = millis();
          return;
        case Card::AUTHORIZED:
          setState(State::OPENING);
          return;
        default:
          setState(State::REJECT);
          return;
      }
      return;

    case State::REJECT:
      setState(State::IDLE);
      return;

    case State::CONTROL:
      if (!isCardScaned()) {
        return;
      }
      switch (checkCard(cardUID)) {
        case Card::RESET:
          setState(State::RESET);
          return;
        case Card::LOCK:
          setState(State::LOCKED);
          return;
        case Card::UNKNOWN:
          setState(State::ADD_CARD);
          return;
      }
       if (millis() - stoper > CONTROL_TIMEOUT) {
        setState(State::IDLE);
        return;
      }
      return;

    case State::ADD_CARD:
      if (addCardToAuthorizedList(cardUID)) {
        setState(State::IDLE);
      } else {
        setState(State::ERROR);
      }
      return;

    case State::RESET:
      if (truncateDatabase()) {
        setState(State::IDLE);
      } else {
        setState(State::ERROR);
      }
      return;

    case State::LOCKED:
      if (!isCardScaned()) {
        return;
      }
      switch (checkCard(cardUID)) {
        case Card::MASTER:
          setState(State::IDLE);
          return;
        default:
          return;
      }
      return;

    case State::OPENING:
      unlockLock();
      setState(State::WAITING_FOR_OPEN);
      return;

    case State::WAITING_FOR_OPEN:
      if (isLockOpened()) {
        setState(State::OPEN);
      } else {
        setState(State::ERROR);
      }
      return;

    case State::OPEN:
      if (isLockOpened()) {
        setState( State::WAITING_FOR_CLOSE);
        stoper = millis();
      }
      return;

    case State::ERROR:
      setState(State::IDLE);
      return;

    case State::WAITING_FOR_CLOSE:
      if (!isLockOpened()) {
        setState(State::CLOSED);
      }
      if (millis() - stoper > WAITING_FOR_CLOSE_TIMEOUT) {
        makeNoise(State::WAITING_FOR_CLOSE);
      }
      return;

    case State::CLOSED:
      setState(State::IDLE);
      return;
  }
}

