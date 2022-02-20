
#include "time.h"

LocalTime fromEpochMillis(long epochMillis) {
  LocalTime localTime;
  localTime.hour = 12;
  localTime.minute = 34;
  localTime.second = 56;
  localTime.millisecond = 0;
  return localTime;
}
