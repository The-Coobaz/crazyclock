#include "LocalDateTimeConverter.h"

#include <Time.h>
#include <Timezone.h>

LocalDateTimeConverter::LocalDateTimeConverter() {}

// The change to summertime in Poland takes place on the last Sunday of March.
// Poland switches back to regular time on the last Sunday of October.
// https://cyclinghikes.com/what-time-is-poland-now/#Do_clocks_change_in_Poland
TimeChangeRule stdRule = {"CET", Last, Sun, Nov, 2, 60};
TimeChangeRule dstRule = {"CEST", Last, Sun, Mar, 2, 120};
Timezone pl(dstRule, stdRule);

LocalDateTimeConverter LocalDateTimeConverter::PL = LocalDateTimeConverter();

unsigned long LocalDateTimeConverter::fromEpochSeconds(unsigned long epochSeconds) {
  return pl.toLocal(epochSeconds);
}

unsigned long LocalDateTimeConverter::fromUtc(int year, int month, int day, int hour, int minute, int second) {
  // similar to setTime method
  tmElements_t tmElements;

  tmElements.Year = year - 1970;
  tmElements.Month = month;
  tmElements.Day = day;
  tmElements.Hour = hour;
  tmElements.Minute = minute;
  tmElements.Second = second;
  
  time_t utcTime = makeTime(tmElements);
  return fromEpochSeconds(utcTime);
}
