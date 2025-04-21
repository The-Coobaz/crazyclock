#include "WarsawTimeConverter.h"

char *WarsawTimeConverter::toWarsawTime(unsigned long epochSeconds,
                                        int millis) {

  sprintf(this->_warsawTime, "01:00:00.000", epochSeconds, millis);
  return this->_warsawTime;
};
