#ifndef CRAZYCLOCK_FAKE_TIME_STARTING_POINT_H
#define CRAZYCLOCK_FAKE_TIME_STARTING_POINT_H

class FakeTimeStartingPoint {
private:
  unsigned long epochSeconds;
  int millis;
  double scalingFactor;

public:
  void reset(unsigned long epochSeconds, int millis);
  void update(double scalingFactor, unsigned long epochSeconds, int millis);

  void formatEpoch(char *buffer);
};

#endif
