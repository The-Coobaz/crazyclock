#ifndef CRAZYCLOCK_HARDWARE_CHECK_H
#define CRAZYCLOCK_HARDWARE_CHECK_H

#define RTC_ERROR_STATUS 3
#define INVALID_REAL_TIME 2

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DS3231.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "../LcdDisplay/LcdDisplay.h"

void beginLCD(hd44780_I2Cexp *lcd, int cols, int rows);
void beginRTC(hd44780_I2Cexp *lcd, DS3231 *rtc);

bool isWiFiAvailable(LcdDisplay lcdDisplay, const char *ssid,
                     const char *password);

void checkRTC(hd44780_I2Cexp *lcd, DS3231 *rtc);
bool epochSecondsAreCorrect(unsigned long realTimeEpochSeconds);

#endif
