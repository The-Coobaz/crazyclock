#ifndef CRAZYCLOCK_FAKE_TIME_STARTING_POINT_H
#define CRAZYCLOCK_FAKE_TIME_STARTING_POINT_H

class FakeTimeStartingPoint {
private:
  double scalingFactor;
  // we need real time to correctly calculate time passed
  unsigned long epochSeconds;
  int millis;
  // we need fake time to know how to calculate fake time
  unsigned long fakeEpochSeconds;
  int fakeMillis;

public:
  /**
   * @brief Resets the starting point so that the clock shows real time.
   */
  void reset(unsigned long epochSeconds, int millis);

  /**
   * @brief Creates new starting point after the scaling factor is changed.
   */
  void update(double scalingFactor, unsigned long epochSeconds, int millis,
              unsigned long fakeEpochSeconds, int fakeMillis);

  /**
   * @brief Prints epoch seconds and millis into buffer (with leading spaces).
   */
  void formatEpoch(char *buffer);
};

#endif
