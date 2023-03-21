
#include "computeFakeTime.h"

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
 * @return Time fake passed time
 */
Time scalePassedTime(Time passedTime, double scalingFactor) {
  Time result;
  if (scalingFactor == 0.0) {
    result.seconds = 0;
    result.millis = 0;
  } else if (scalingFactor == 1.0) {
    result.seconds = passedTime.seconds;
    result.millis = passedTime.millis;
  } else {
    // maybe optimize for large / small scaling factors in future...
    result.seconds = 1;
    result.millis = 1;
  }
  return result;
}
