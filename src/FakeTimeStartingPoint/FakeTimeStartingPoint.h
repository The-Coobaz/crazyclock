#ifndef CRAZYCLOCK_FAKE_TIME_STARTING_POINT_H
#define CRAZYCLOCK_FAKE_TIME_STARTING_POINT_H

class FakeTimeStartingPoint {

public:
  unsigned long epochSeconds;
  int millis;
  double scalingFactor;

  void resetAt(unsigned long epochSeconds, int millis);
};

#endif
