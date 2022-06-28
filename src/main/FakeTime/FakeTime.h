
#ifndef CRAZYCLOCK_FAKE_TIME
#define CRAZYCLOCK_FAKE_TIME

class FakeTime {

private:
  double _timeScaling;
  long _scalingUpdatedAt;

public:
  FakeTime(long realMillis);

  int setScaling(double newScaling, long realMillis);

  long getFakeMillis(long realMillis);
};

#endif
