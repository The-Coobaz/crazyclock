#ifndef CRAZYCLOCK_COMPUTE_FAKE_SECONDS_H
#define CRAZYCLOCK_COMPUTE_FAKE_SECONDS_H

class Time {

public:
  unsigned long seconds;
  int millis;
};

Time calculatePassedTime(unsigned long epochSecondsForStartPoint,
                         int millisForStartPoint,
                         unsigned long epochSecondsForNow, int millisForNow);

long long scalePassedTime(Time passedTime, double scalingFactor);

#endif
