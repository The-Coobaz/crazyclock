#ifndef CRAZYCLOCK_COMPUTE_FAKE_SECONDS_H
#define CRAZYCLOCK_COMPUTE_FAKE_SECONDS_H

class Time {

public:
  unsigned long seconds;
  int millis;
};

/**
 * @brief Computes the epoch seconds (UTC) of current fake time.
 *
 * Does it by getting the start point (this is the moment of last change
 * of scaling factor) and adding the time passed from that moment until now,
 * multiplied by scaling factor:
 *
 * fakeTime = programStartedAt + (timePassed * scalingFactor)
 *
 * Scaling factor can be less than one, zero, or even negative,
 * if the fake time should fly backward.
 *
 * @param epochSecondsForStartPoint - epoch seconds (UTC) of start point
 * @param millisForStartPoint - millis part of te second of start point
 * @param epochSecondsForNow - epoch seconds (UTC) of current time
 * @param millisForNow - millis part of the current epoch seconds
 * @param scalingFactor - how many times faster the fake time should flow
 * @return Time
 */
Time computeFakeTime(unsigned long epochSecondsForStartPoint,
                     int millisForStartPoint, unsigned long epochSecondsForNow,
                     int millisForNow, double scalingFactor);

/**
 * @brief Calculates seconds and millis passed between two UTC time points
 *
 * @param epochSecondsForStartPoint
 * @param millisForStartPoint
 * @param epochSecondsForNow
 * @param millisForNow
 * @return Time
 */
Time calculateTimePassed(unsigned long epochSecondsForStartPoint,
                         int millisForStartPoint,
                         unsigned long epochSecondsForNow, int millisForNow);

Time calculateScaledDistance(Time distance, double scalingFactor);

#endif
