#include "FakeTimeStartingPoint.h"

#include <stdio.h>

void FakeTimeStartingPoint::reset(unsigned long epochSeconds, int millis) {
  this->update(1.0, epochSeconds, millis, epochSeconds, millis);
};

void FakeTimeStartingPoint::update(double scalingFactor,
                                   unsigned long epochSeconds, int millis,
                                   unsigned long fakeEpochSeconds,
                                   int fakeMillis) {
  this->epochSeconds = epochSeconds;
  this->millis = millis;
  this->scalingFactor = scalingFactor;
};

void FakeTimeStartingPoint::formatEpoch(char *buffer) {
  sprintf(buffer, "%12lu.%03d", this->epochSeconds, this->millis);
};
