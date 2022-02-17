#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "SSID";
const char *password = "PASS";

int tH = 0, tM = 0, tS = 0; // ntp data
int mH, mM, mS;             // crazydata
int tick = 1000;  // initial value of tick =1s
char zerro[] = {"0"};

unsigned long myMillis;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org",3600,60000);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

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
}
void whatTime() {
  timeClient.update();
  tH = timeClient.getHours();
  tM = timeClient.getMinutes();
  tS = timeClient.getSeconds();
  Serial.println((String)tH + ":" + tM + ":" + tS);
}

void checkEncoder() {
  // TODO
  // Here we listen to the rotations of the encoder, modify the tick and check
  // if encoder is not pressed (then reset and return to ntp time) here we will
  // need a flag variable showing that the time was altered from NTP. This will
  // be used in showMe
}
void ticTac() {
  
  // here the clock works
  
  if ((millis() >= myMillis) and tick > 0) {
    mS++;
    myMillis = (millis() + tick);
    showMe();
  } else if ((millis() >= myMillis) and tick < 0) {
    mS--;
    myMillis = (millis() + tick);
    showMe();
  } // if our second has passed and tick is minus, decrement;

  if (mS == 59 and tick>0) {
    mS = -1;
    mM++; // if second has passed and tick is plus, increment minute
    }
  
  if (mS < 0 and tick<0) {
    mS = mS + 60;
    mM--; // if second has passed and tick is minus, decrement minute
  }
  if (mM == 59 and tick>0) {
    mM = -1;
    mH++; // if minute has passed and tick is plus, increment hour
    }
  
  if (mM < 0 and tick<0) {
    mM = mM + 59;
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
  if (mM <10){Serial.print(zerro[0]);}
  Serial.print((String)mM+":");
  if (mS <10){Serial.print(zerro[0]);}
  Serial.print(mS);
  Serial.println(); //debug output
  // here we show the result on the screen TODO
}
