#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H

#include "LocalDateTime.h"

/**
 * Calculates correct local time based on UTC time
 * or UTC number of seconds since January 1st, 1970.
 */
class LocalDateTimeConverter {

private:
  LocalDateTimeConverter(int timezoneId);
  int timezoneId;

public:
  static LocalDateTimeConverter UTC;
  static LocalDateTimeConverter PL;

  LocalDateTime fromUtc(int year, int month, int day, int hour, int minute,
                        int second);
  unsigned long toLocalSeconds(unsigned long epochSeconds);
  LocalDateTime fromUtc(unsigned long epochSeconds);
};

#endif
