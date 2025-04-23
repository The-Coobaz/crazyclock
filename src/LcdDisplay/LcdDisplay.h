#pragma once

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include <array>
#include <string>

class LcdDisplay {
public:
  LcdDisplay();

  void setLine1(char *line);
  void setLine2(char *line);

  void print(char *text);
  void clear();

  hd44780_I2Cexp lcd;
private:
  static const uint8_t cols = 16;
  static const uint8_t rows = 2;

  char blankLine[cols + 1];

  void clearLine(uint8_t row);
};
