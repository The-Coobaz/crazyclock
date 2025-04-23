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

private:
  static const uint8_t columns = 16;
  static const uint8_t rows = 2;
  static char blankLine[columns + 1];
  hd44780_I2Cexp lcd;
};
