#include "HardwareCheck.h"

void beginLCD(hd44780_I2Cexp *lcd, int cols, int rows) {
  Serial.println("Starting LCD...");
  int status = lcd->begin(cols, rows);
  if (status) {
    // non zero status means it was unsuccesful
    Serial.print("LCD error status: ");
    Serial.println(status);
    // blink error code using the onboard LED if possible (stops program)
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

bool isWiFiAvailable(LcdDisplay lcdDisplay, const char *ssid,
                     const char *password) {
  Serial.println("Waiting for WiFi");
  lcdDisplay.setLine1("Waiting for WiFi");
  // provided in examples of WiFi library with a comment:
  // > Explicitly set the ESP8266 to be a WiFi-client,
  // > otherwise, it by default, would try to act as both
  // > a client and an access-point
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  for (int n = 0; (n < 30) && (WiFi.status() != WL_CONNECTED); n++) {
    delay(500);
    Serial.print(".");
    lcdDisplay.print(".");
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to WiFi network: ");
    Serial.println(ssid);
    return true;
  } else {
    Serial.print("Can NOT connect to WiFi network: ");
    Serial.println(ssid);
    return false;
  }
}

void checkRTC(hd44780_I2Cexp *lcd, DS3231 *rtc) {

  DateTime fromRtc = RTClib::now();
  bool isSecondOk = fromRtc.second() < 60 && fromRtc.second() >= 0;
  bool isMinuteOk = fromRtc.minute() < 60 && fromRtc.minute() >= 0;
  bool isHourOk = fromRtc.hour() < 24 && fromRtc.hour() >= 0;
  bool readOk = isSecondOk && isMinuteOk && isHourOk;

  if (!readOk) {
    Serial.print("RTC error. Hour: ");
    Serial.print(fromRtc.hour());
    Serial.print("minute: ");
    Serial.print(fromRtc.minute());
    Serial.print("second: ");
    Serial.println(fromRtc.second());
    hd44780::fatalError(RTC_ERROR_STATUS);
  } else {
    Serial.println("RTC started");
  }
}

bool epochSecondsAreCorrect(unsigned long realTimeEpochSeconds) {
  if (realTimeEpochSeconds < 946684801) {
    Serial.println("Real time should NOT be before 2000-01-01");
    hd44780::fatalError(INVALID_REAL_TIME);
    return false;
  }
  if (realTimeEpochSeconds > 4102444799) {
    Serial.println("Real time should NOT be after 2099-12-31");
    hd44780::fatalError(INVALID_REAL_TIME);
    return false;
  }
  // prints error to console but doesn't stop execution
  if (realTimeEpochSeconds < 1640999044) {
    Serial.println("Real time should NOT be before 2022-01-01");
    return false;
  }
  if (realTimeEpochSeconds > 1924920244) {
    Serial.println("Real time should NOT be after 2030-12-31");
    return false;
  }
  return true;
}
