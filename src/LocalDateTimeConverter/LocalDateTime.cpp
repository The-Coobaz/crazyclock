#include "LocalDateTime.h"

LocalDateTime::LocalDateTime(unsigned long epochSeconds,
                             unsigned long localSeconds) {
  _epochSeconds = epochSeconds;
  _localSeconds = localSeconds;
};

unsigned long LocalDateTime::getEpochSeconds() { return this->_epochSeconds; };

unsigned long LocalDateTime::getLocalSeconds() { return this->_localSeconds; };
