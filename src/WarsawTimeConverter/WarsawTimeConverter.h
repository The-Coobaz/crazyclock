#pragma once

#include <Timezone.h>
#include <stdio.h>

class WarsawTimeConverter {

public:
  char *toWarsawTime(unsigned long epochSeconds, int millis);

private:
  char *_warsawTime = new char[12];
};
