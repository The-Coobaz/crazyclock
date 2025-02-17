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
#include "src/HardwareCheck/HardwareCheck.h"
#include "src/LocalDateTimeConverter/LocalDateTimeConverter.h"
#include "src/ScalingFactorChange/ScalingFactorChange.h"
#include "src/ntpClient/ntpClient.h"

const char *ssid = "SSID";
const char *password = "PASS";

LocalDateTimeConverter plDateTimeConverter = LocalDateTimeConverter::PL;

char formattedTimeBuffer[20] = "<initial value>";

// Example for ESP8266 NodeMCU with input signals on pin D5 and D6
#define ROTARY_ENCODER_CLK D5
#define ROTARY_ENCODER_DT D6
#define ROTARY_ENCODER_BUTTON_PIN D7

Debouncer debouncer(ROTARY_ENCODER_BUTTON_PIN, 30, Debouncer::Active::L,
                    Debouncer::DurationFrom::TRIGGER);

unsigned long epochSeconds;
unsigned long currentSecond;

unsigned long newSecondStartedAtMillis;
unsigned long currentMillis;

ScalingFactorChange scalingFactorChange;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
RotaryEncoder encoder(ROTARY_ENCODER_DT, ROTARY_ENCODER_CLK,
                      RotaryEncoder::LatchMode::TWO03);
// interrupts added for better handling of rotary encoder
IRAM_ATTR void tick() {
  encoder.tick(); // just call tick() to check the state.
};
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
  Serial.println("Attaching encoder interrupts...");
  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_DT), tick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_CLK), tick, CHANGE);

  debouncer.subscribe(Debouncer::Edge::RISE, [](const int state) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Resetting");
    pos = 0;
    encoder.setPosition(0);

    DateTime now = RTClib::now();
    int millisOfSecond = millis() - newSecondStartedAtMillis;
    if (millisOfSecond >= 1000) {
      Serial.print("WARNING: Unexpected millis value: ");
      Serial.println(millisOfSecond);
    }
    scalingFactorChange.reset(now.unixtime(), millisOfSecond);
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
    epochSeconds = retrieveEpochSeconds(&timeClient);
    if (epochSecondsAreCorrect(epochSeconds)) {
      rtc.setEpoch(epochSeconds);
      Serial.print("RTC was set to UTC time epoch seconds: ");
      Serial.println(epochSeconds);

      sprinfLocalTime(formattedTimeBuffer, epochSeconds, currentMillis);
      Serial.print("In Europe/Warsaw timezone it is: ");
      Serial.print(formattedTimeBuffer);
    }
  }
  checkRTC(&lcd, &rtc);

  lcd.clear();

  int sec = rtc.getSecond();
  Serial.print("Current second value: ");
  Serial.println(sec);
  while (sec == rtc.getSecond()) {
    // waits until new second starts
  }
  newSecondStartedAtMillis = millis();
  Serial.print("New second started at millis: ");
  Serial.println(newSecondStartedAtMillis);

  DateTime now = RTClib::now();
  int millisOfSecond = millis() - newSecondStartedAtMillis;
  scalingFactorChange.reset(now.unixtime(), millisOfSecond);

  scalingFactorChange.formatEpoch(formattedTimeBuffer);
  Serial.print("Program Started at epoch seconds (UTC): ");
  Serial.println(formattedTimeBuffer);
}

void loop() {
  debouncer.update();
  DateTime now = RTClib::now();
  epochSeconds = now.unixtime();
  if (epochSeconds > currentSecond) {
    newSecondStartedAtMillis = millis();
    currentSecond = epochSeconds;
  }

  currentMillis = millis() - newSecondStartedAtMillis;
  if (currentMillis > 1000) {
    // re-adjusting values
    epochSeconds = epochSeconds + (currentMillis / 1000);
    currentMillis = currentMillis % 1000;
  }
  // TODO: calculate fake time
  // fakeTime = programStartedAt + (scalingFactor * timePassed)

  // shows real time local seconds and current millis on LCD
  sprinfLocalTime(formattedTimeBuffer, epochSeconds, currentMillis);
  lcd.setCursor(0, 0);
  lcd.print(formattedTimeBuffer);
  sprintfRaw(formattedTimeBuffer, epochSeconds, currentMillis);
  lcd.setCursor(0, 1);
  lcd.print(formattedTimeBuffer);
  checkRotaryEncoder(&scalingFactorChange);
}

void sprinfLocalTime(char *buffer, unsigned long epochSeconds, int millis) {
  LocalDateTime localDateTime = plDateTimeConverter.fromUtc(epochSeconds);
  int hour = localDateTime.getLocalTimeFragment(HOURS);
  int minutes = localDateTime.getLocalTimeFragment(MINUTES);
  int seconds = localDateTime.getLocalTimeFragment(SECONDS);
  sprintf(buffer, "    %02d:%02d:%02d.%03d", hour, minutes, seconds, millis);
}

void sprintfRaw(char *buffer, unsigned long epochSeconds, int millis) {
  sprintf(buffer, "%12lu.%03d", epochSeconds, millis);
}

void checkRotaryEncoder(ScalingFactorChange *scalingFactorChange) {
  int newPos = encoder.getPosition();

  if (pos != newPos) {
    pos = newPos;
    // for now we calculate scaling factor as simple linear function
    double scaling = (pos * 0.1) + 1;
    // TODO: we will need to update attributes of scaling factor change

    Serial.print("New rotary position: ");
    Serial.println(pos);
    Serial.print("New scaling factor: ");
    Serial.println(scaling);
  }
}
