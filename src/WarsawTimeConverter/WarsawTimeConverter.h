#pragma once

#include <Timezone.h>

class WarsawTimeConverter {

public:
  void toWarsawTime(unsigned long epochSeconds, int millis);

private:
  char *_warsawTime = new char[12];
};
