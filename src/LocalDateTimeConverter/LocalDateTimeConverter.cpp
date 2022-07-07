#include "LocalDateTimeConverter.h"

#include <Time.h>
#include <Timezone.h>

const int utcId = 0;
const int plId = 1;

// The change to summertime in Poland takes place on the last Sunday of March.
// Poland switches back to regular time on the last Sunday of October.
// https://cyclinghikes.com/what-time-is-poland-now/#Do_clocks_change_in_Poland
TimeChangeRule stdRule = {"CET", Last, Sun, Nov, 2, 60};
TimeChangeRule dstRule = {"CEST", Last, Sun, Mar, 3, 120};
Timezone pl(dstRule, stdRule);

LocalDateTimeConverter::LocalDateTimeConverter(int tzId) {
  timezoneId = tzId;
}

unsigned long LocalDateTimeConverter::fromUtc(unsigned long epochSeconds) {
  if(this->timezoneId == utcId) {
    return epochSeconds;
  } else {
    return pl.toLocal(epochSeconds);
  }
}

LocalDateTimeConverter LocalDateTimeConverter::UTC = LocalDateTimeConverter(utcId);
LocalDateTimeConverter LocalDateTimeConverter::PL = LocalDateTimeConverter(plId);
