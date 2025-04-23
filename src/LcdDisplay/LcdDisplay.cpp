#include "LcdDisplay.h"

void initializeBlankLine(char *line, int length) {
  for (int i = 0; i < length; i++) {
    line[i] = ' ';
  }
  line[length] = '\0';
}

LcdDisplay::LcdDisplay() {
  initializeBlankLine(this->blankLine, LcdDisplay::columns);
  Serial.println("Starting LCD...");
  this->lcd = hd44780_I2Cexp();

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
  this->clearLine(0);
  this->lcd.print(line);
};

void LcdDisplay::setLine2(char *line) {
  this->clearLine(1);
  this->lcd.print(line);
};

void LcdDisplay::print(char *text) { this->lcd.print(text); }

void LcdDisplay::clearLine(uint8_t row) {
  this->lcd.setCursor(0, row);
  this->lcd.print(this->blankLine);
  this->lcd.setCursor(0, row);
}