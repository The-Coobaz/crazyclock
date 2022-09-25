#include "PassedTime.h"

PassedTime::PassedTime(long seconds, long millis) {
  this->_seconds = seconds;
  this->_millis = millis;
};

PassedTime PassedTime::fromDistance(long startMillis, long endMillis) {
  long long passedMillis = endMillis - startMillis;
  return PassedTime(0L, passedMillis);
};

long PassedTime::getSeconds() { return this->_seconds; }

long PassedTime::getMillis() { return this->_millis; }
