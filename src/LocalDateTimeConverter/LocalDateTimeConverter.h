#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H

#include "LocalDateTime.h"

/**
 * Calculates correct local time based on UTC time
 * or UTC number of seconds since January 1st, 1970.
 */
class LocalDateTimeConverter {

private:
  int timezoneId;

  LocalDateTimeConverter(int timezoneId);

  unsigned long toLocalSeconds(unsigned long epochSeconds);

public:
  static LocalDateTimeConverter UTC;
  static LocalDateTimeConverter PL;

  LocalDateTime fromUtc(int year, int month, int day, int hour, int minute,
                        int second);
  LocalDateTime fromUtc(unsigned long epochSeconds);
};

#endif
