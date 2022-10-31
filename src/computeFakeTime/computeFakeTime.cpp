
#include "computeFakeTime.h"

Time computeFakeTime(unsigned long epochSecondsForStartPoint,
                     int millisForStartPoint, unsigned long epochSecondsForNow,
                     int millisForNow, double scalingFactor) {
  Time result;
  result.seconds = epochSecondsForStartPoint;
  result.millis = millisForStartPoint;
  return result;
}

Time calculateTimePassed(unsigned long epochSecondsForStartPoint,
                         int millisForStartPoint,
                         unsigned long epochSecondsForNow, int millisForNow) {
  Time result;
  int passedMillis = millisForNow - millisForStartPoint;
  int passedSeconds = epochSecondsForNow - epochSecondsForStartPoint;
  result.seconds = passedSeconds;
  result.millis = passedMillis;
  return result;
}

Time calculateScaledDistance(Time distance, double scalingFactor) {}
