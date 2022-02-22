#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
// #include <RotaryEncoder.h>

#include "time.h"

const char *ssid = "SSID";
const char *password = "PASS";

int mH, mM, mS;   // crazydata
int tick = 1000;  // initial value of tick =1s
char zerro[] = { "0" };

unsigned long
  myMillis;  // maybe myMillis should be a function returning the result?

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
hd44780_I2Cexp lcd;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // waits for serial port to be ready
  };

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status)  // non zero status means it was unsuccesful
  {
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status);  // does not return
  }

  timeClient.begin();
  whatTime();
  //tick=-1000; //For debug purposes
  myMillis = (millis() + tick);
}

void loop() {
  // checkEncoder();
  ticTac();
  }
void whatTime() {  // this function synchronises time with NTP and normalizes the
                   // tick to 1 second
  timeClient.update();
  mH = timeClient.getHours();
  mM = timeClient.getMinutes();
  mS = timeClient.getSeconds();
  tick = 1000;
  Serial.println((String)mH + ":" + mM + ":" + mS);
}

void checkEncoder() {
  // TODO
  // Here we listen to the rotations of the encoder, modify the tick and check
  // if encoder is not pressed (then reset and return to ntp time) here we will
  // need a flag variable showing that the time was altered from NTP. This will
  // be used in "showMe" to show if we can trust the clock ;)
  // if button pressed invoke "whatTime"
}
void ticTac() {

  // here the clock works

  if ((millis() >= myMillis) and tick > 0) {
    showMe(); //first show, then add second
    mS++;
    myMillis = (millis() + tick);

  } else if ((millis() >= myMillis) and tick < 0) {
    showMe();
    mS--;
    myMillis = (millis() + abs(tick));

  }  // if our second has passed and tick is minus, decrement;

  if (mS == 60 and tick > 0) {
    mS = 0;
    mM++;  // if second has passed and tick is plus, increment minute
  }
  
  if (mM == 60 and tick > 0) {
    mM = 0;// if minute has passed and tick is plus, increment hour
  }
  
  if (mS < 0 and tick < 0) {
    mS = 59;
    mM--;  // if second has passed and tick is minus, decrement minute
  }
 
  if (mM < 0 and tick < 0) {
    mM = 59;
    mH--;  // if minute has passed and tick is minus, decrement hour
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
  Serial.println();  // debug output
  // here we show the result on the screen TODO
  lcd.setCursor(0, 0);
  if (mH < 10) {
    lcd.print(String("0"));
    lcd.setCursor(1, 0);
  }
  lcd.print(String(mH) + String(":"));
  //lcd.print(":");

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
  lcd.print(String("tick:") + String(tick) + String("ms"));
  // this will need concatenation in order to print it on the screen
}
