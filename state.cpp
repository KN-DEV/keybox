#include "state.h"
LiquidCrystal_I2C lcd(0x27, LCD_CELS, LCD_ROWS);
State state;
void setupState() {
  lcd.init();
  lcd.backlight();
  setState(State::IDLE);
}
State getState() {
  return state;
};
void setState(State s) {
  state = s;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(getTextForEnum((int) getState()));
  playMelody(getState());
};
const char * getTextForEnum( int enumVal ) {
  return StateLabel[enumVal];
};
