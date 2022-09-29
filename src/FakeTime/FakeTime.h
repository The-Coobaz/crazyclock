#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

class FakeTime {

private:
  short _hour;
  short _minutes;
  short _seconds;

public:
  FakeTime(short hour, short minutes, short seconds);

  short hour();
  short minutes();
  short seconds();
};

#endif
