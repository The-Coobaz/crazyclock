#ifndef CRAZYCLOCK_SCALING_FACTOR_CHANGE_H
#define CRAZYCLOCK_SCALING_FACTOR_CHANGE_H

class ScalingFactorChange {
private:
  double scalingFactor;
  // we need the real time when the scaling factor was changed
  unsigned long epochSeconds;
  int millis;
  // and also fake time of that change
  unsigned long fakeEpochSeconds;
  int fakeMillis;

public:
  /**
   * @brief Resets the starting point so that the clock shows real time.
   */
  void reset(unsigned long epochSeconds, int millis);

  /**
   * @brief Prints real epoch seconds and millis of the change into buffer
   * (with leading spaces).
   */
  void formatEpoch(char *buffer);
};

#endif
