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
    // This will happen when millis() function resets to zero
    // after approximately 50 days of program running
    passedMillis = (ARDUINO_MAX_MILLIS)-newSecondStartedAt + currentMillis;
  }
  // long type should be enough for seconds for reasonably small durations
  long passedSeconds = passedMillis / 1000;
  return TimeDuration(passedSeconds, passedMillis % 1000);
};
