#include "state.h"
LiquidCrystal_I2C lcd(0x27, LCD_CELS, LCD_ROWS);
State _state;
void setupState() {
  lcd.init();
  lcd.backlight();
  setState(State::IDLE);
}
State getState() {
  return _state;
};
void setState(State state) {
  _state = state;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(getTextForEnum((int) getState()));
};
const char * getTextForEnum( int enumVal ) {
  return StateLabel[enumVal];
};
