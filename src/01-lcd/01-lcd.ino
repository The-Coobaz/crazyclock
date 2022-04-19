#include "LiquidCrystal_I2C.h"
#include <Wire.h>

// initialize the liquid crystal library
// the first parameter is the I2C address
// the second parameter is how many rows are on your screen
// the third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {

  // initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();

  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("It works!");
  lcd.noBlink();
  lcd.cursor();
}

void loop() {
  for (uint8_t i = 0; i < 19; i++) {
    lcd.setCursor(i, 2);
    delay(250);
  }
  for (uint8_t i = 19; i > 0; i--) {
    lcd.setCursor(i, 2);
    delay(250);
  }
}
