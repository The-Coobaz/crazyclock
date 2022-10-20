#ifndef CRAZYCLOCK_HARDWARE_CHECK_H
#define CRAZYCLOCK_HARDWARE_CHECK_H

#define RTC_ERROR_STATUS 3

#include <DS3231.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

void beginLCD(hd44780_I2Cexp *lcd, int cols, int rows);
void beginRTC(hd44780_I2Cexp *lcd, DS3231 *rtc);

bool isWiFiAvailable(hd44780_I2Cexp *lcd, const char *ssid,
                     const char *password);

void checkRTC(hd44780_I2Cexp *lcd, DS3231 *rtc);

#endif
