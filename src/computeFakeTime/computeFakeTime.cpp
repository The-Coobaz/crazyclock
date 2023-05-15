
#include "computeFakeTime.h"

Time::Time() {
  seconds = 0;
  millis = 0;
};

void Time::set(unsigned long seconds, int millis) {
  this->seconds = seconds;
  this->millis = millis;
};

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

/**
 * @brief multiplies passed time by scaling factor
 *
 * @param passedTime time passed from the start point
 * @param scalingFactor how many times faster (or slower) crazyclock should go
 * @return fake passed time in milliseconds (might be negative)
 */
long long scalePassedTime(Time passedTime, double scalingFactor) {
  long long result;
  if (scalingFactor == 0.0) {
    result = 0;
  } else if (scalingFactor == 1.0) {
    result = passedTime.seconds * 1000 + passedTime.millis;
  } else {
    long long scaledSeconds = scalingFactor * passedTime.seconds * 1000;
    long long scaledMillis = scalingFactor * passedTime.millis;
    result = scaledSeconds + scaledMillis;
  }
  return result;
}
