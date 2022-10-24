
#include "FakeTime.h"
#include <stdio.h>

FakeTime::FakeTime() {
  this->_h = 0;
  this->_m = 0;
  this->_s = 0;
}

int FakeTime::setTime(int h, int m, int s) {
  if (h < 0 || h > 23) {
    return INCORRECT_HOUR;
  }
  if (m < 0 || m > 59) {
    return INCORRECT_MINUTE;
  }
  if (s < 0 || s > 59) {
    return INCORRECT_SECOND;
  }
  this->_h = h;
  this->_m = m;
  this->_s = s;
  return SUCCESS;
}

void FakeTime::formatTime(char *targetBuffer) {
  sprintf(targetBuffer, "%02d:%02d:%02d", this->_h, this->_m, this->_s);
}
