#include "LocalDateTime.h"

LocalDateTime::LocalDateTime(unsigned long localSeconds) {
  _localSeconds = localSeconds;
};

unsigned long LocalDateTime::getLocalSeconds() { return this->_localSeconds; };

int LocalDateTime::getLocalTimeFragment(int unit) {
  int timeFragment;
  switch (unit) {
  case SECONDS:
    timeFragment = this->_localSeconds % 60;
    break;
  case MINUTES:
    timeFragment = (this->_localSeconds / 60) % 60;
    break;
  case HOURS:
    timeFragment = (this->_localSeconds / 3600) % 24;
    break;
  default:
    timeFragment = -1;
  }
  return timeFragment;
}
