
#include "Arduino.h"
#include "state.h"
#include "pitches.h"
#include "card.h"

#include "database.h"
#include "door.h"
#include "noise.h"
#include "config.h"





// https://github.com/firebull/arduino-edb
//
// https://www.arduino.cc/en/Tutorial/ToneMelody?from=Tutorial.Tone



// Do Zrobienia
//------------------------------------------



/**
   Dodaje identyfikator zeskanowanej karty do listy zautoryzowanych kart
*/



/**
   czyta kartę wybiera z niej UID i zapamiętuje do zmienniej
   @TODO
  http://stackoverflow.com/questions/2404439/how-do-i-bit-shift-a-long-by-more-
  than-32-bits

*/




void setup() {
  setUpDoor();

  lcd.init();
  lcd.backlight();
  setState(State::IDLE);
  configureRFID();
  configureDatabase();
};


void loop() {
  switch (getState()) {
    case State::IDLE:
      if (!isCardScaned()) {
        return;
      }
      switch (checkCard()) {
        case Card::MASTER:
          setState(State::CONTROL);
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

      switch (checkCard()) {
        case Card::RESET:
          setState(State::RESET);
          return;
        case Card::LOCK:
          setState(State::LOCKED);
          return;
        case Card::UNKNOWN:
          setState(State::ADD_CARD);
          return;
        case Card::MASTER:
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
      switch (checkCard()) {
        case Card::MASTER:
          setState(State::IDLE);
          return;
        default:
          return;
      }
      return;

    case State::OPENING:
      unlockDoor();
      setState(State::WAITING_FOR_OPEN);
      return;

    case State::WAITING_FOR_OPEN:
      if (doorStatus()) {
        setState(State::OPEN);
      } else {
        setState(State::ERROR);
      }
      return;

    case State::OPEN:
      if (!doorStatus()) {
        setState( State::WAITING_FOR_CLOSE);
      }
      return;

    case State::ERROR:
      setState(State::IDLE);
      return;

    case State::WAITING_FOR_CLOSE:
      if (doorStatus()) {
        setState(State::OPEN);
      } else {
        setState(State::CLOSED);
      }
      return;

    case State::CLOSED:
      setState(State::IDLE);
      return;
  }
}

