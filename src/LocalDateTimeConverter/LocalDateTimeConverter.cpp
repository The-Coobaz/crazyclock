#include "LocalDateTimeConverter.h"
#include "LocalDateTime.h"

#include <Timezone.h>

const int utcId = 0;
const int plId = 1;

// The change to summertime in Poland takes place on the last Sunday of March.
// Poland switches back to regular time on the last Sunday of October.
// https://cyclinghikes.com/what-time-is-poland-now/#Do_clocks_change_in_Poland
TimeChangeRule stdRule = {"CET", Last, Sun, Oct, 3, 60};
TimeChangeRule dstRule = {"CEST", Last, Sun, Mar, 2, 120};
Timezone pl(dstRule, stdRule);

LocalDateTimeConverter::LocalDateTimeConverter(int tzId) { timezoneId = tzId; }

LocalDateTime LocalDateTimeConverter::fromUtc(unsigned long epochSeconds) {
  return LocalDateTime(this->toLocalSeconds(epochSeconds));
}

unsigned long
LocalDateTimeConverter::toLocalSeconds(unsigned long epochSeconds) {
  unsigned long localSeconds;
  if (this->timezoneId == plId) {
    localSeconds = pl.toLocal(epochSeconds);
  } else {
    localSeconds = epochSeconds;
  }
  return localSeconds;
}

LocalDateTimeConverter LocalDateTimeConverter::UTC =
    LocalDateTimeConverter(utcId);
LocalDateTimeConverter LocalDateTimeConverter::PL =
    LocalDateTimeConverter(plId);
