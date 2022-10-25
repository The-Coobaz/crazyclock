#include <DS3231.h>
#include <Debouncer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <RotaryEncoder.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
// https://forum.arduino.cc/t/how-to-include-from-subfolder-of-sketch-folder/428039/9
#include "src/FakeTime/FakeTime.h"
#include "src/HardwareCheck/HardwareCheck.h"
#include "src/LocalDateTimeConverter/LocalDateTimeConverter.h"

const char *ssid = "SSID";
const char *password = "PASS";

LocalDateTimeConverter plDateTimeConverter = LocalDateTimeConverter::PL;

char formattedTimeBuffer[19] = "<initial value>";

// Example for ESP8266 NodeMCU with input signals on pin D5 and D6
#define ROTARY_ENCODER_CLK D5
#define ROTARY_ENCODER_DT D6
#define ROTARY_ENCODER_BUTTON_PIN D7

// for rotary encoder switch active is low state
Debouncer debouncer(ROTARY_ENCODER_BUTTON_PIN, 50, Debouncer::Active::L,
                    Debouncer::DurationFrom::TRIGGER);

unsigned long myMillis;
unsigned long epochSeconds;
unsigned long localEpochSeconds;

byte secondFromRtc;
byte currentSecond;
unsigned long newSecondStartedAtMillis;
unsigned long currentMillis;

unsigned long programStartedSeconds;
unsigned long programStartedMillis;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
RotaryEncoder encoder(ROTARY_ENCODER_DT, ROTARY_ENCODER_CLK,
                      RotaryEncoder::LatchMode::TWO03);
int pos = 0;
int buttonState = 0;
DS3231 rtc;

void setup() {
  pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
  delay(2000);
  pinMode(LED_BUILTIN, OUTPUT);
  debouncer.subscribe(Debouncer::Edge::RISE, [](const int state) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Resetting");
    // TODO: reset = current pos should now be considered as "zero"
    DateTime now = RTClib::now();
    programStartedSeconds = now.unixtime();
  });
  debouncer.subscribe(Debouncer::Edge::FALL, [](const int state) {
    // turns off built-in led
    digitalWrite(LED_BUILTIN, LOW);
  });

  Serial.begin(115200);
  while (!Serial) {
    // waits for serial port to be ready
  }
  Serial.println("\n================\ncrazyclock\n================");

  beginLCD(&lcd, LCD_COLS, LCD_ROWS);
  beginRTC(&lcd, &rtc);
  // bool wifiAvailable = isWiFiAvailable(&lcd, ssid, password);
  bool wifiAvailable = false;
  if (wifiAvailable) {

    bool isNtpAvailable = retrieveEpochTimeFromNTP(lcd, &epochSeconds);
    if (isNtpAvailable) {

      Serial.println("Updating RTC with time from NTP...");
      LocalDateTime localDateTime = plDateTimeConverter.fromUtc(epochSeconds);
      int mH = localDateTime.getLocalTimeFragment(HOURS);
      int mM = localDateTime.getLocalTimeFragment(MINUTES);
      int mS = localDateTime.getLocalTimeFragment(SECONDS);
      rtc.setHour(mH);
      rtc.setMinute(mM);
      rtc.setSecond(mS);
    }
  }
  checkRTC(&lcd, &rtc);

  lcd.clear();

  currentSecond = rtc.getSecond();
  Serial.print("Current second value: ");
  Serial.println(currentSecond);
  while (currentSecond == rtc.getSecond()) {
    // waits until new second starts
  }
  newSecondStartedAtMillis = millis();
  // increases value of current second
  currentSecond++;
  Serial.print("New second started at millis: ");
  Serial.println(newSecondStartedAtMillis);

  DateTime now = RTClib::now();
  programStartedSeconds = now.unixtime();
  programStartedMillis = millis() - newSecondStartedAtMillis;
  prettyPrint(formattedTimeBuffer, programStartedSeconds, programStartedMillis);
  Serial.print("Program Started at: ");
  Serial.println(formattedTimeBuffer);
}

void loop() {
  debouncer.update();
  secondFromRtc = rtc.getSecond();
  if (currentSecond < secondFromRtc) {
    newSecondStartedAtMillis = millis();
    currentSecond = secondFromRtc;
  }

  DateTime now = RTClib::now();
  localEpochSeconds = now.unixtime();
  currentMillis = millis() - newSecondStartedAtMillis;
  if (currentMillis > 1000) {
    // re-adjusting values
    localEpochSeconds = localEpochSeconds + (currentMillis / 1000);
    currentMillis = currentMillis % 1000;
  }

  prettyPrint(formattedTimeBuffer, localEpochSeconds, currentMillis);
  lcd.setCursor(0, 1);
  lcd.print(formattedTimeBuffer);
  checkRotaryEncoder();
}

void prettyPrint(char *buffer, unsigned long epochSeconds, int millis) {
  sprintf(buffer, "%9d.%03d", epochSeconds, millis);
}

bool retrieveEpochTimeFromNTP(hd44780_I2Cexp lcd, unsigned long *epochSeconds) {
  bool isNtpTimeRetrieved = false;
  Serial.println("Checking NTP...");
  timeClient.begin();
  if (timeClient.update()) {
    Serial.println("NTP time update successful");
    *epochSeconds = timeClient.getEpochTime();
    isNtpTimeRetrieved = true;
  } else {
    Serial.println("NTP time update failed");
  }
  return isNtpTimeRetrieved;
}

void checkRotaryEncoder() {
  encoder.tick();
  int newPos = encoder.getPosition();

  if (pos != newPos) {
    Serial.print("New rotary position: ");
    Serial.println(newPos);
    pos = newPos;
    // TODO: calculate scaling factor based on rotary encoder position
  }
}
