#ifndef CRAZYCLOCK_PASSED_MILLIS_H
#define CRAZYCLOCK_PASSED_MILLIS_H

// https://www.arduino.cc/reference/en/language/functions/time/millis/
// https://en.cppreference.com/w/cpp/language/types#Properties
#define ARDUINO_MAX_MILLIS 4294967295UL

class PassedTime {

private:
  long _seconds;
  long _millis;

  PassedTime(long seconds, long millis);

public:
  long getSeconds();
  long getMillis();

  static PassedTime fromDistance(unsigned long newSecondStartedAt,
                                 unsigned long currentMillis);
};

#endif
