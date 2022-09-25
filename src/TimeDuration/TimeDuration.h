#ifndef CRAZYCLOCK_PASSED_MILLIS_H
#define CRAZYCLOCK_PASSED_MILLIS_H

// https://www.arduino.cc/reference/en/language/functions/time/millis/
// https://en.cppreference.com/w/cpp/language/types#Properties
#define ARDUINO_MAX_MILLIS 4294967295UL

class TimeDuration {

private:
  long _seconds;
  long _millis;

  TimeDuration(long seconds, long millis);

public:
  long getSeconds();
  long getMillis();

  /**
   * Can be used to calculate current time with milliseconds precision.
   * With the usage of Arduino millis() function:
   * 1. We observe when the second is changed (i.e. from real-time clock)
   * 2. By getting millis() we can calculate time elapsed from that change
   */
  static TimeDuration fromDistance(unsigned long newSecondStartedAt,
                                   unsigned long currentMillis);
};

#endif
