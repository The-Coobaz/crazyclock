
#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

#include <Arduino.h>

class FakeTime {

private:
  double _timeScaling;
  long _scalingUpdatedAt;

public:
  FakeTime(long realMillis);

  int setScaling(double newScaling, long realMillis);

  long getFakeMillis(long realMillis);
};

#endif
