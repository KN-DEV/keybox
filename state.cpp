#include "state.h"

LiquidCrystal_I2C lcd(0x27, LCD_CELS, LCD_ROWS);
State state;

void setState(State s) {
    state = s;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(getTextForEnum((int) getState()));
};

State getState() {
    return state;
};
const char * getTextForEnum( int enumVal ) {
    return EnumStrings[enumVal];
};
