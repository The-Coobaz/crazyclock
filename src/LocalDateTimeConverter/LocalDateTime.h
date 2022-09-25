#ifndef CRAZYCLOCK_LOCAL_DATE_TIME_H
#define CRAZYCLOCK_LOCAL_DATE_TIME_H

#define HOURS 100
#define MINUTES 101
#define SECONDS 102

/**
 * Representation of local time converted from UTC.
 */
class LocalDateTime {

private:
  unsigned long _localSeconds;

public:
  LocalDateTime(unsigned long localSeconds);

  unsigned long getLocalSeconds();

  int getLocalTimeFragment(int unit);
};

#endif
