#include "PassedTime.h"

PassedTime::PassedTime(long seconds, long millis) {
  this->_seconds = seconds;
  this->_millis = millis;
};

PassedTime PassedTime::fromDistance(long startMillis, long endMillis) {
  return PassedTime(0L, 0L);
};

long PassedTime::getSeconds() { return this->_seconds; }

long PassedTime::getMillis() { return this->_millis; }
