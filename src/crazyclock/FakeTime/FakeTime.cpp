#include "FakeTime.h"

FakeTime::FakeTime(long realMillis) {
  _timeScaling = 1.0;
  _scalingUpdatedAt = realMillis;
}

int FakeTime::setScaling(double newScaling, long realMillis) { return 0; }

long FakeTime::getFakeMillis(long realMillis) { return realMillis; }
