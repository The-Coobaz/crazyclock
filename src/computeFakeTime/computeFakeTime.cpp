
#include "computeFakeTime.h"

Fake computeFakeTime(unsigned long epochSecondsForStartPoint,
                     int millisForStartPoint, unsigned long epochSecondsForNow,
                     int millisForNow, double scalingFactor) {
  Fake result;
  result.epochSeconds = epochSecondsForStartPoint;
  result.millis = millisForStartPoint;
  return result;
}
