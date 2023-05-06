#include "ntpClient.h"

#include <Arduino.h>
#include <WiFiUdp.h>
#include <Wire.h>

bool isNtpUpdateAvailable(NTPClient *ntpClient) {
  bool isNtpAvailable = false;
  Serial.println("Checking NTP...");
  // Interesting observation: update() function returns false
  // if there was no need to update the time from server (default is 60 seconds)
  if (ntpClient->update()) {
    Serial.println("NTP time update is available");
    isNtpAvailable = true;
  } else {
    Serial.println("Can not update from NTP");
  }
  return isNtpAvailable;
}

unsigned long retrieveEpochSeconds(NTPClient *ntpClient) {
  // initializes result to 0 as a failure code
  // (we assume the program is NOT run on 1970-01-01)
  unsigned long result = 0;
  ntpClient->begin();

  if (isNtpUpdateAvailable(ntpClient)) {
    Serial.println("Updating RTC with UTC time from NTP...");
    if (ntpClient->isTimeSet()) {
      Serial.println("Getting time from NTP...");
      result = ntpClient->getEpochTime();
      Serial.print("Response from NTP client: ");
      Serial.println(result);
    } else {
      Serial.println("Unexpected errors in NTP client");
    }
  } else {
    Serial.println("NTP is not available");
  }

  ntpClient->end();
  return result;
};
