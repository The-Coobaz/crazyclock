#include "FakeTime.h"

FakeTime::FakeTime(short hour, short minutes, short seconds) {
  this->_hour = hour;
  this->_minutes = minutes;
  this->_seconds = seconds;
}

short FakeTime::hour() { return this->_hour; }

short FakeTime::minutes() { return this->_minutes; }

short FakeTime::seconds() { return this->_seconds; }

FakeTime FakeTime::plusMillis(long millis) {
  // TODO: implement this correctly
  return FakeTime(-1, -2, -3);
}
