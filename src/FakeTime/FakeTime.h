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
  FakeTime(int h, int m, int s);

  int formatTime(char *targetBuffer);

  /**
   * Updates the Fake time so that it show the hour, minute and second
   * in future (after given milliseconds value).
   */
  void plusMillis(long millis);
};

#endif
