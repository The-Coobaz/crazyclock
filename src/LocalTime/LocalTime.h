#ifndef CRAZYCLOCK_FAKE_TIME_H
#define CRAZYCLOCK_FAKE_TIME_H

#include "LocalTime.h"
//#include <Timezone.h>

class LocalTime {

public:
  LocalTime();

  unsigned long fromEpochSeconds(unsigned long epochSeconds);
};

#endif
