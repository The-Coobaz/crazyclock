#pragma once

#include <Timezone.h>
#include <stdio.h>

class WarsawTimeConverter {

public:
  WarsawTimeConverter();
  char *toWarsawTime(unsigned long epochSeconds, int millis);

private:
  char *_warsawTime;
  Timezone *plTimezone;
};
