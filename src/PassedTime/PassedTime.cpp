#include "PassedTime.h"

PassedTime::PassedTime(long seconds, long millis) {
  this->_seconds = seconds;
  this->_millis = millis;
};

long PassedTime::getSeconds() { return this->_seconds; }

long PassedTime::getMillis() { return this->_millis; }

PassedTime PassedTime::fromDistance(unsigned long newSecondStartedAt,
                                    unsigned long currentMillis) {
  long long passedMillis;
  if (newSecondStartedAt <= currentMillis) {
    passedMillis = currentMillis - newSecondStartedAt;
  } else {
    // this can happen if millis() functions resets to zero
    passedMillis = ((ARDUINO_MAX_MILLIS)-newSecondStartedAt) + currentMillis;
  }
  long passedSeconds = passedMillis / 1000;
  return PassedTime(passedSeconds, passedMillis % 1000);
};
