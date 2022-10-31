
#include "computeFakeTime.h"

Time computeFakeTime(unsigned long epochSecondsForStartPoint,
                     int millisForStartPoint, unsigned long epochSecondsForNow,
                     int millisForNow, double scalingFactor) {}

Time calculatePassedTime(unsigned long epochSecondsForStartPoint,
                         int millisForStartPoint,
                         unsigned long epochSecondsForNow, int millisForNow) {
  Time result;
  int passedMillis;
  int passedSeconds = epochSecondsForNow - epochSecondsForStartPoint;

  bool millisIncreased = millisForNow >= millisForStartPoint;
  if (millisIncreased) {
    passedMillis = millisForNow - millisForStartPoint;
  } else {
    passedMillis = (1000 - millisForStartPoint) + millisForNow;
    passedSeconds--;
  }
  result.seconds = passedSeconds;
  result.millis = passedMillis;
  return result;
}

Time calculateScaledPassedTime(Time distance, double scalingFactor) {}
