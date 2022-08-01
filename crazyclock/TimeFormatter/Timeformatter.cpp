
#include "TimeFormatter.h"

#include <stdio.h>

int formatTime(int hour, int minute, int second, char *targetBuffer) {
  if (hour < 0 || hour > 23) {
    return INCORRECT_HOUR;
  }
  if (minute < 0 || minute > 59) {
    return INCORRECT_MINUTE;
  }
  if (second < 0 || second > 59) {
    return INCORRECT_SECOND;
  }

  char hourStr[3];
  char minuteStr[3];
  char secondStr[3];

  sprintf(hourStr, "%02d", hour);
  sprintf(minuteStr, "%02d", minute);
  sprintf(secondStr, "%02d", second);

  sprintf(targetBuffer, "%s:%s:%s", hourStr, minuteStr, secondStr);
  return SUCCESS;
}
