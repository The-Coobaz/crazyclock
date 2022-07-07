#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

class LocalDateTimeConverter {

private:
  LocalDateTimeConverter();

public:
  static LocalDateTimeConverter PL;

  unsigned long fromEpochSeconds(unsigned long epochSeconds);

  unsigned long fromUtc(int year, int month, int day, int hour, int minute, int second);
};

#endif
