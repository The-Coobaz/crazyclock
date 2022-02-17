#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "SSID";
const char *password = "PASS";

int tH = 0, tM = 0, tS = 0; // ntp data
int mH, mM, mS;             // crazydata
unsigned long tick = 1000;  // initial value of tick =1s
int tick = 1000;  // initial value of tick =1s

unsigned long myMillis;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "tempus1.gum.gov.pl");
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org",3600,60000);

void setup() {
  Serial.begin(115200);
@ -24,18 +25,22 @@ void setup() {

  timeClient.begin();
  whatTime();
  mH=tH;
  mM=tM;
  mS=tS;
  myMillis = (millis() + tick);
}

void loop() {
  checkEncoder();
  ticTac();
  showMe();
}
void whatTime() {
  timeClient.update();
  tH = timeClient.getHours();
  tM = timeClient.getMinutes();
  tS = timeClient.getSeconds();
  Serial.println((String)tH + ":" + tM + ":" + tS);
}

void checkEncoder() {
@ -46,18 +51,21 @@ void checkEncoder() {
  // be used in showMe
}
void ticTac() {
  // debug output
  Serial.println((String)mH + ":" + mM + ":" + mS);
  
  // here the clock works
  myMillis = millis() + tick;
  if (myMillis = millis() && tick > 0) {
  
  if ((millis() >= myMillis) and tick > 0) {
    mS++;
  } else if (myMillis = millis() && tick < 0) {
    myMillis = (millis() + tick);
    showMe();
  } else if ((millis() >= myMillis) and tick < 0) {
    mS--;
    myMillis = (millis() + tick);
    showMe();
  } // if our second has passed and tick is minus, decrement;

  if (mS = 60) {
    mS = mS - 60;
  if (mS == 59) {
    mS = mS - 59;
    if (tick > 0) {
      mM++; // if second has passed and tick is plus, increment minute
    }
@ -66,8 +74,8 @@ void ticTac() {
    mS = mS + 60;
    mM--; // if second has passed and tick is minus, decrement minute
  }
  if (mM = 60) {
    mM = mM - 60;
  if (mM == 59) {
    mM = mM - 59;
    if (tick > 0) {
      mH++; // if minute has passed and tick is plus, increment hour
    }
@ -76,13 +84,14 @@ void ticTac() {
    mM = mM + 59;
    mH--; // if minute has passed and tick is minus, decrement hour
  }
  if (mH = 24) {
  if (mH == 24) {
    mH - 24;
  }
  if (mH = -1) {
  if (mH == -1) {
    mH = mH + 24;
  };
}
void showMe() {
  Serial.println((String)mH + ":" + mM + ":" + mS); //debug outpu
  // here we show the result on the screen TODO
}
