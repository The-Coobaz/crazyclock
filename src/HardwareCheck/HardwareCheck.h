#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

void beginLCD(hd44780_I2Cexp *lcd, int cols, int rows);

bool isWiFiAvailable(hd44780_I2Cexp *lcd, const char *ssid, const char *password);
