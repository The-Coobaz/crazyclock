#include "ScalingFactorChange.h"

#include <stdio.h>

void ScalingFactorChange::reset(unsigned long epochSeconds, int millis) {
  this->scalingFactor = scalingFactor;
  this->epochSeconds = epochSeconds;
  this->millis = millis;
  this->fakeEpochSeconds = epochSeconds;
  this->fakeMillis = millis;
};

void ScalingFactorChange::formatEpoch(char *buffer) {
  sprintf(buffer, "%12lu.%03d", this->epochSeconds, this->millis);
};
