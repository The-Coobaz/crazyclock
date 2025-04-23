#pragma once

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

class LcdDisplay {
public:
  LcdDisplay();

private:
  hd44780_I2Cexp lcd;
};
