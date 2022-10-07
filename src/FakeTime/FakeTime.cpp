
#include "FakeTime.h"
#include <stdio.h>

FakeTime::FakeTime(int h, int m, int s) {
  this->_h = h;
  this->_m = m;
  this->_s = s;
}

int FakeTime::formatTime(char *targetBuffer) {
  if (this->_h < 0 || this->_h > 23) {
    return INCORRECT_HOUR;
  }
  if (this->_m < 0 || this->_m > 59) {
    return INCORRECT_MINUTE;
  }
  if (this->_s < 0 || this->_s > 59) {
    return INCORRECT_SECOND;
  }

  sprintf(targetBuffer, "%02d:%02d:%02d", this->_h, this->_m, this->_s);
  return SUCCESS;
}

void FakeTime::plusMillis(long millis) {
  // TODO: implement how the time changes when milliseconds are added
}
