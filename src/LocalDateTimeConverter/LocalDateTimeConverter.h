#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H

#include "LocalDateTime.h"

/**
 * Converter to for getting correct local time
 * based on UTC time or number seconds from January 1st, 1970.
 * Helps getting the local time from NTP server
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
  LocalDateTime fromUtc(unsigned long epochSeconds);
};

#endif
