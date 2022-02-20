#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <U8g2lib.h>

const char *ssid = "SSID";
const char *password = "PASS";

int mH, mM, mS;             // crazydata
int tick = 1000;  // initial value of tick =1s
char zerro[] = {"0"};

unsigned long myMillis; //maybe myMillis should be a function returning the result?

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
   myMillis = (millis() + tick);
}

void loop() {
  checkEncoder();
  ticTac();
  showMe();
}
void whatTime() { //this function synchronises time with NTP and normalizes the tick to 1 second
  timeClient.update();
  mH = timeClient.getHours();
  mM = timeClient.getMinutes();
  mS = timeClient.getSeconds();
  tick=1000;
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
    mS++;
    myMillis = (millis() + tick);
   
  } else if ((millis() >= myMillis) and tick < 0) {
    mS--;
    myMillis = (millis() + tick);
    
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
   //this will need concatenation in order to print it on the screen
}
