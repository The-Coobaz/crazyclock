#include "FakeTimeStartingPoint.h"

void FakeTimeStartingPoint::resetAt(unsigned long epochSeconds, int millis) {
  this->epochSeconds = epochSeconds;
  this->millis = millis;
  this->scalingFactor = 1.0;
};
