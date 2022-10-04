
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

  char hourStr[3];
  char minuteStr[3];
  char secondStr[3];

  sprintf(hourStr, "%02d", this->_h);
  sprintf(minuteStr, "%02d", this->_m);
  sprintf(secondStr, "%02d", this->_s);

  sprintf(targetBuffer, "%s:%s:%s", hourStr, minuteStr, secondStr);
  return SUCCESS;
}