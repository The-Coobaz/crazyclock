#include "LcdDisplay.h"

LcdDisplay::LcdDisplay() {
  const int LCD_COLS = 16;
  const int LCD_ROWS = 2;
  Serial.println("Starting LCD...");
  this->lcd = hd44780_I2Cexp();

};
