#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_H

/**
 * Representation of time converted from UTC to local time.
 */
class LocalDateTime {

private:
  unsigned long _epochSeconds;
  unsigned long _localSeconds;

public:
  LocalDateTime(unsigned long epochSeconds, unsigned long localSeconds);
  unsigned long getEpochSeconds();
  unsigned long getLocalSeconds();
};

#endif
