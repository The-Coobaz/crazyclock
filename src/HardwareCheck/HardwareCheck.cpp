#include "HardwareCheck.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

void beginLCD(hd44780_I2Cexp *lcd, int cols, int rows) {
  Serial.println("Starting LCD...");
  int status = lcd->begin(cols, rows);
  if (status) {
    // non zero status means it was unsuccesful
    Serial.print("LCD error status: ");
    Serial.println(status);
    // blink error code using the onboard LED if possible (stops program
    // execution)
    hd44780::fatalError(status);
  } else {
    Serial.println("LCD Started");
  }
}

void beginRTC(hd44780_I2Cexp *lcd, DS3231 *rtc) {
  Serial.println("Starting RTC...");
  bool mode12 = false;
  rtc->setClockMode(mode12);
  Serial.println("RTC set to 24-hour mode");
}

bool isWiFiAvailable(hd44780_I2Cexp *lcd, const char *ssid,
                     const char *password) {
  Serial.println("Waiting for WiFi");
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Waiting for WiFi");
  lcd->setCursor(0, 1);

  WiFi.begin(ssid, password);
  for (int n = 0; (n < 30) && (WiFi.status() != WL_CONNECTED); n++) {
    delay(500);
    Serial.print(".");
    lcd->print(".");
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to WiFi network: ");
    Serial.println(ssid);
    return true;
  } else {
    Serial.println("Can NOT connect to WiFi");
    return false;
  }
}
