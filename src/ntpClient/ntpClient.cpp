#include "ntpClient.h"

#include <Arduino.h>
#include <WiFiUdp.h>
#include <Wire.h>

bool updateTimeFromNtpServer(NTPClient *ntpClient) {
  bool retrievedFromNtpServer = false;
  Serial.println("Checking NTP...");
  if (ntpClient->update()) {
    retrievedFromNtpServer = true;
  } else {
    // Interesting observation:
    // update() function only check the server if the time is not fresh
    // (if the last update is older than 60 seconds ago)
    Serial.println("Did not connect to NTP server");
  }
  return retrievedFromNtpServer;
}

unsigned long retrieveEpochSeconds(NTPClient *ntpClient) {
  // initializes result to 0 as a failure code
  // (we assume the program is NOT run on 1970-01-01)
  unsigned long result = 0;
  ntpClient->begin();

  if (updateTimeFromNtpServer(ntpClient)) {
    Serial.println("Updated UTC time from NTP");
  }
  if (ntpClient->isTimeSet()) {
    Serial.println("Getting epoch seconds...");
    result = ntpClient->getEpochTime();
    Serial.print("Response from NTP client: ");
    Serial.println(result);
  } else {
    Serial.println("Could not get time from NTP");
  }

  ntpClient->end();
  return result;
};
