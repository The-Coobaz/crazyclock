#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

class LocalTime {

public:
  LocalTime();

  unsigned long fromEpochSeconds(unsigned long epochSeconds);
};

#endif
