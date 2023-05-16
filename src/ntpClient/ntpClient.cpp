#include "ntpClient.h"

#include <Arduino.h>
#include <WiFiUdp.h>
#include <Wire.h>

bool updateTimeFromNtpServer(NTPClient *ntpClient) {
  bool isNtpAvailable = false;
  Serial.println("Checking NTP...");
  // Interesting observation: update() function returns false
  // if there was no need to update the time from server (default is 60 seconds)
  if (ntpClient->update()) {
    Serial.println("NTP time was updated from server");
    isNtpAvailable = true;
  } else {
    Serial.println("NTP server not checked");
  }
  return isNtpAvailable;
}

unsigned long retrieveEpochSeconds(NTPClient *ntpClient) {
  // initializes result to 0 as a failure code
  // (we assume the program is NOT run on 1970-01-01)
  unsigned long result = 0;
  ntpClient->begin();

  if (updateTimeFromNtpServer(ntpClient)) {
    Serial.println("Updated UTC time from NTP");
    if (ntpClient->isTimeSet()) {
      Serial.println("Getting epoch seconds...");
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
