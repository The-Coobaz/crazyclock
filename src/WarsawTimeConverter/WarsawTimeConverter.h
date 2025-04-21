#pragma once

#include <Timezone.h>
#include <stdio.h>

class WarsawTimeConverter {

public:
  WarsawTimeConverter();
  /**
   * This updates the buffer to contain Warsaw time for given UTC epoch seconds.
   */
  void fromUtc(unsigned long utcEpochSeconds, int millis);
  /**
   * Warsaw time will be updated in-place at this memory address.
   */
  char *formatted();

private:
  char *_warsawTime;
  Timezone *plTimezone;
};
