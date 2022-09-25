#include "TimeDuration.h"

TimeDuration::TimeDuration(long seconds, long millis) {
  this->_seconds = seconds;
  this->_millis = millis;
};

long TimeDuration::getSeconds() { return this->_seconds; }

long TimeDuration::getMillis() { return this->_millis; }

TimeDuration TimeDuration::fromDistance(unsigned long newSecondStartedAt,
                                    unsigned long currentMillis) {
  long long passedMillis;
  if (newSecondStartedAt <= currentMillis) {
    passedMillis = currentMillis - newSecondStartedAt;
  } else {
    // this can happen if millis() functions resets to zero
    passedMillis = ((ARDUINO_MAX_MILLIS)-newSecondStartedAt) + currentMillis;
  }
  long passedSeconds = passedMillis / 1000;
  return TimeDuration(passedSeconds, passedMillis % 1000);
};
