#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

#include <Time.h>

class LocalDateTimeConverter {

private:
  LocalDateTimeConverter(int timezoneId);
  int timezoneId;

public:
  static LocalDateTimeConverter UTC;
  static LocalDateTimeConverter PL;

  unsigned long fromUtc(unsigned long epochSeconds);
};

#endif
