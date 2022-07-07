#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_CONVERTER_H

#include "LocalDateTime.h"

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
