#include "PassedTime.h"

PassedTime::PassedTime(long seconds, long millis) {
  this->_seconds = seconds;
  this->_millis = millis;
};

PassedTime PassedTime::fromDistance(long startMillis, long endMillis) {
  // result is long, because we expect non-negative arguments
  // (they should be greater or equal zero)
  long passedMillis;
  if (startMillis <= endMillis) {
    passedMillis = endMillis - startMillis;
  } else {
    // this can happen if millis() functions resets to zero
    passedMillis = ((ARDUINO_MAX_MILLIS) - startMillis) + endMillis;
  }
  long passedSeconds = passedMillis / 1000;
  return PassedTime(passedSeconds, passedMillis % 1000);
};

long PassedTime::getSeconds() { return this->_seconds; }

long PassedTime::getMillis() { return this->_millis; }
