
#include "time.h"

long epochMillis() { return 0; }

LocalTime toWarsawTime(long epochMillis) {
  LocalTime localTime;
  localTime.hour = 12;
  localTime.minute = 34;
  localTime.second = 56;
  return localTime;
}
