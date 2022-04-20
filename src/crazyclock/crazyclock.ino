#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <RotaryEncoder.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

const char *ssid = "SSID";
const char *password = "PASS";

int mH, mM, mS;  // crazydata
int tick = 1000; // initial value of tick =1s
bool change;     // change of time
char zerro[] = {"0"};

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO_EVERY)
// Example for Arduino UNO with input signals on pin 2 and 3
#define PIN_IN1 2
#define PIN_IN2 3

#elif defined(ESP8266)
// Example for ESP8266 NodeMCU with input signals on pin D5 and D6
#define PIN_IN1 12
#define PIN_IN2 14
#endif
unsigned long
    myMillis; // maybe myMillis should be a function returning the result?

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

void setup() {
  pinMode(13, INPUT);
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }
  lcd.print("Waiting for WiFi");
  lcd.setCursor(0, 1);
  Serial.begin(115200);
  while (!Serial) {
    // waits for serial port to be ready
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.print(".");
  }

  lcd.clear();

  timeClient.begin();
  whatTime();
  // tick=-1000; //For debug purposes
  myMillis = (millis() + tick);
}

void loop() {
  checkEncoder();
  ticTac();
}
void whatTime() { // this function synchronises time with NTP and normalizes the
  // tick to 1 second
  timeClient.update();
  mH = timeClient.getHours();
  mM = timeClient.getMinutes();
  mS = timeClient.getSeconds();
  tick = 1000;
  change = false;
  Serial.println((String)mH + ":" + mM + ":" + mS);
}

void checkEncoder() {

  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();

  if (pos != newPos) {
    change = true;
    if (newPos > pos) {
      tick = tick + 50;
    } else {
      tick = tick - 50;
    }

    pos = newPos;
    myMillis = (millis() + tick); // reset counting after tick change
    showMe();                     // show the result immediately
  }
  if (digitalRead(13) == 0) { // if reset pressed, return to NTP time
    whatTime();
  }
}
void ticTac() {

  // here the clock works

  if ((millis() >= myMillis) and tick > 0) {
    showMe(); // first show, then add second
    mS++;
    myMillis = (millis() + tick);

  } else if ((millis() >= myMillis) and tick < 0) {
    showMe();
    mS--;
    myMillis = (millis() + abs(tick));

  } // if our second has passed and tick is minus, decrement;

  if (mS == 60 and tick > 0) {
    mS = 0;
    mM++; // if second has passed and tick is plus, increment minute
  }

  if (mM == 60 and tick > 0) {
    mM = 0; // if minute has passed and tick is plus, increment hour
    mH++;
  }

  if (mS < 0 and tick < 0) {
    mS = 59;
    mM--; // if second has passed and tick is minus, decrement minute
  }

  if (mM < 0 and tick < 0) {
    mM = 59;
    mH--; // if minute has passed and tick is minus, decrement hour
  }
  if (mH == 24) {
    mH - 24;
  }
  if (mH == -1) {
    mH = mH + 24;
  };
}
void showMe() {
  Serial.print((String)mH + ":");
  if (mM < 10) {
    Serial.print(zerro[0]);
  }
  Serial.print((String)mM + ":");
  if (mS < 10) {
    Serial.print(zerro[0]);
  }
  Serial.print(mS);
  Serial.println(); // debug output
  // here we show the result on the screen TODO
  lcd.setCursor(0, 0);
  if (mH < 10) {
    lcd.print(String("0"));
    lcd.setCursor(1, 0);
  }
  lcd.print(String(mH) + String(":"));
  // lcd.print(":");

  if (mM < 10) {
    lcd.setCursor(3, 0);
    lcd.print("0");
  }
  lcd.print(String(mM) + String(":"));
  if (mS < 10) {

    lcd.print(String("0"));
  }
  lcd.print(String(mS));
  lcd.setCursor(0, 1);
  lcd.print(String("tick:") + String(tick) + String("ms "));
  if (change) {
    lcd.setCursor(15, 0);
    lcd.print("?");
  } else {
    lcd.setCursor(15, 0);
    lcd.print(" ");
  };
}
