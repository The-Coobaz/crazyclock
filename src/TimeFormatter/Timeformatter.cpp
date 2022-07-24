
#include "TimeFormatter.h"

#include <stdio.h>

int formatTime(int hour, int minute, int second, char *targetBuffer) {
    char hourStr[] = "00";
    char minuteStr[] = "00";
    char secondStr[] = "00";

    sprintf(hourStr, "%02d", hour);
    sprintf(minuteStr, "%02d", minute);
    sprintf(secondStr, "%02d", second);

    sprintf(targetBuffer, "%s:%s:%s", hourStr, minuteStr, secondStr);
    return SUCCESS;
}
