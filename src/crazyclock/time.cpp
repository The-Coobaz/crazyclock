#include "time.h"

LocalTime::LocalTime(int h, int m, int s) {
  hour = h;
  minute = m;
  second = s;
  millisecond = 0;
};

LocalTime fromEpochMillis(long epochMillis) {
  int seconds = (epochMillis / (1000)) % 60;
  int minutes = (epochMillis / (1000 * 60)) % 60;
  int hours = (epochMillis / (1000 * 60 * 60)) % 24;
  LocalTime localTime(hours, minutes, seconds);
  return localTime;
}
