#include "LocalDateTimeConverter.h"
#include "LocalDateTime.h"

#include <Time.h>
#include <Timezone.h>

const int utcId = 0;
const int plId = 1;

// The change to summertime in Poland takes place on the last Sunday of March.
// Poland switches back to regular time on the last Sunday of October.
// https://cyclinghikes.com/what-time-is-poland-now/#Do_clocks_change_in_Poland
TimeChangeRule stdRule = {"CET", Last, Sun, Oct, 3, 60};
TimeChangeRule dstRule = {"CEST", Last, Sun, Mar, 2, 120};
Timezone pl(dstRule, stdRule);

LocalDateTimeConverter::LocalDateTimeConverter(int tzId) {
  timezoneId = tzId;
}

LocalDateTime LocalDateTimeConverter::fromUtc(int year, int month, int day, int hour, int minute, int second) {
  TimeElements timeElements;
  timeElements.Year = year - 1970;
  timeElements.Month = month;
  timeElements.Day = day;
  timeElements.Hour = hour;
  timeElements.Minute = minute;
  timeElements.Second = second;

  unsigned long seconds = makeTime(timeElements);

  return this->fromUtc(seconds);
}

LocalDateTime LocalDateTimeConverter::fromUtc(unsigned long epochSeconds) {
  unsigned long localSeconds;
  if(this->timezoneId == plId) {
    localSeconds = pl.toLocal(epochSeconds);
  } else {
    localSeconds = epochSeconds;
  }
  return LocalDateTime(epochSeconds, localSeconds);
}

LocalDateTimeConverter LocalDateTimeConverter::UTC = LocalDateTimeConverter(utcId);
LocalDateTimeConverter LocalDateTimeConverter::PL = LocalDateTimeConverter(plId);
