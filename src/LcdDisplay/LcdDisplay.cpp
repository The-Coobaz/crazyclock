#include "LcdDisplay.h"

LcdDisplay::LcdDisplay() {
  Serial.println("Starting LCD...");
  this->lcd = hd44780_I2Cexp();
  for (int i = 0; i < LcdDisplay::columns; i++) {
    LcdDisplay::blankLine[i] = ' ';
  }
  LcdDisplay::blankLine[LcdDisplay::columns] = '\0';

  int status = this->lcd.begin(LcdDisplay::columns, LcdDisplay::rows);
  if (status) {
    Serial.print("LCD error status: ");
    Serial.println(status);
    // blink error code using the onboard LED if possible (stops program)
    hd44780::fatalError(status);
  } else {
    Serial.println("LCD Started");
  }

  lcd.clear();
};

void LcdDisplay::setLine1(char *line) {
  this->lcd.setCursor(0, 0);
  this->lcd.print(LcdDisplay::blankLine);
  this->lcd.print(line);
};
