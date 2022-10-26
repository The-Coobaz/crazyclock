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

Debouncer debouncer(ROTARY_ENCODER_BUTTON_PIN, 30, Debouncer::Active::L,
                    Debouncer::DurationFrom::TRIGGER);

unsigned long epochSeconds;
unsigned long localEpochSeconds;

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
  pinMode(LED_BUILTIN, OUTPUT);
  // gives some time for the hardware to start
  delay(800);
  Serial.begin(115200);
  while (!Serial) {
    // waits for serial port to be ready
  }
  // gives some time to connect Serial monitor
  delay(2000);

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

  Serial.println("\n================\ncrazyclock\n================");

  beginLCD(&lcd, LCD_COLS, LCD_ROWS);
  beginRTC(&lcd, &rtc);
  bool wifiAvailable = isWiFiAvailable(&lcd, ssid, password);
  if (wifiAvailable) {

    timeClient.begin();
    bool isNtpAvailable = tryNTPTimeClientUpdate(timeClient);
    if (isNtpAvailable) {

      Serial.println("Updating RTC with UTC time from NTP...");
      if (timeClient.update() && timeClient.isTimeSet()) {
        epochSeconds = timeClient.getEpochTime();
        rtc.setEpoch(epochSeconds);
        Serial.print("RTC was set to UTC time epoch seconds: ");
        Serial.println(epochSeconds);
      } else {
        Serial.println("Unexpected errors in NTP client");
      }
    } else {
      Serial.println("NTP is not available");
    }
    timeClient.end();
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
  byte rtcSec = rtc.getSecond();
  if (currentSecond < rtcSec) {
    newSecondStartedAtMillis = millis();
    currentSecond = rtcSec;
  }

  DateTime now = RTClib::now();
  localEpochSeconds = now.unixtime();
  currentMillis = millis() - newSecondStartedAtMillis;
  if (currentMillis > 1000) {
    // re-adjusting values
    localEpochSeconds = localEpochSeconds + (currentMillis / 1000);
    currentMillis = currentMillis % 1000;
  }
  // TODO: calculate fake time
  // fakeTime = programStartedAt + (scalingFactor * timePassed)

  // shows real time local seconds and current millis on LCD
  prettyPrint(formattedTimeBuffer, localEpochSeconds, currentMillis);
  lcd.setCursor(0, 1);
  lcd.print(formattedTimeBuffer);
  checkRotaryEncoder();
}

void prettyPrint(char *buffer, unsigned long epochSeconds, int millis) {
  sprintf(buffer, "%12d.%03d", epochSeconds, millis);
}

bool tryNTPTimeClientUpdate(NTPClient timeClient) {
  bool isNtpAvailable = false;
  Serial.println("Checking NTP...");
  if (timeClient.update()) {
    Serial.println("NTP time update successful");
    isNtpAvailable = true;
  } else {
    Serial.println("NTP time update failed");
  }
  return isNtpAvailable;
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
