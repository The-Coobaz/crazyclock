#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

#define SUCCESS 0
#define INCORRECT_HOUR 1
#define INCORRECT_MINUTE 2
#define INCORRECT_SECOND 3

class FakeTime {
private:
  int _h;
  int _m;
  int _s;

public:
  FakeTime();

  int setTime(int h, int m, int s);
  void formatTime(char *targetBuffer);
};

#endif
