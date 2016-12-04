#include "Arduino.h"
#include "state.h"
#include "card.h"
#include "database.h"
#include "lock.h"
#include "melody.h"
#include "keyholder.h"
#include "nonBlockingDelay.h"
#include "config.h"
void setup() {
  setupKeyHolder();
  setupLockSensor();
  setupLock();
  setupState();
  setupRFID();
  setupDatabase();
};

unsigned long previousMillis = 0;
void setTimeForTimeout() {
  previousMillis = millis();
}
bool checkTimeout(unsigned long timeout) {
  return abs(millis() - previousMillis) >= timeout;
}

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
          setTimeForTimeout();
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
      if (checkTimeout(CONTROL_TIMEOUT)) {
        playMelody(State::CONTROL);
        setState(State::IDLE);
        return;
      }
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
    /**
         Jeśli w pobliżu jest karta sprawdzamy czy to karta MASTER jeśli tak przechodzimy w stan IDLE
    */
    case State::LOCKED:
      if (!isCardScaned()) {
        return;
      }
      switch (checkCard(cardUID)) {
        case Card::MASTER:
          setState(State::IDLE);
          return;
      }
      return;
    /**
        Otwieramy zamek jeśli mija LOCK_DELAY zamykamy zamek i przechodzimy w stan WAITING_FOR_OPEN
    */
    case State::OPENING:
      unlockLock();
      setState(State::WAITING_FOR_OPEN);
      setTimeForTimeout();
      return;
    /**
         Sprawdza czy zamek jest otwarty jeśli tak przechodzimy w stan OPEN jeśli nie przechodzimy w stan ERROR
    */
    case State::WAITING_FOR_OPEN:
      if (!checkTimeout(500)) {
        return;
      }
      if (isLockOpened()) {
        setState(State::OPEN);
      } else {
        setState(State::ERROR);
      }
      return;
    /**
         Sprawdza czy zamek jest otwarty i przechodzi w stan WAITING_FOR_CLOSE oraz aktualizuje czas dla timeout
    */
    case State::OPEN:
      playMelody(State::OPEN);
      setState( State::WAITING_FOR_CLOSE);
      setTimeForTimeout();
      return;
    /**
         Ze stanu ERROR przechodzimy w stan IDLE
    */
    case State::ERROR:
      playMelody(State::ERROR);
      nonBlockingDealy(2000);
      setState(State::IDLE);
      return;
    /**
        Sprawdza czy zamek jest nie otwarty i przechodzimy w stan  CLOSED
         Sprawdza czy mineło WAITING_FOR_CLOSE_TIMEOUT i odgrywa dzwięk
    */
    case State::WAITING_FOR_CLOSE:
      if (!isLockOpened()) {
        setState(State::CLOSED);
        return;
      }
      if (checkTimeout( WAITING_FOR_CLOSE_TIMEOUT)) {
        playMelody(State::WAITING_FOR_CLOSE);
      }
      return;
    /**
        Ze stanu CLOSED przechodzimy w stan IDLE
    */
    case State::CLOSED:
      playMelody(State::CLOSED);
      nonBlockingDealy(1500);
      setState(State::IDLE);
      return;
  }
}
