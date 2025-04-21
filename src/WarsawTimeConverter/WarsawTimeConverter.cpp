#include "WarsawTimeConverter.h"

// The change to summertime in Poland takes place on the last Sunday of March.
// Poland switches back to regular time on the last Sunday of October.
// https://cyclinghikes.com/what-time-is-poland-now/#Do_clocks_change_in_Poland
TimeChangeRule standardTimeRule = {"CET", Last, Sun, Oct, 3, 60};
TimeChangeRule daylightSavingTimeRule = {"CEST", Last, Sun, Mar, 2, 120};

WarsawTimeConverter::WarsawTimeConverter() {
  this->plTimezone = new Timezone(standardTimeRule, daylightSavingTimeRule);
  this->_warsawTime = new char[13];
};

int seconds(unsigned long epochSeconds) { return epochSeconds % 60; }

int minutes(unsigned long epochSeconds) { return (epochSeconds / 60) % 60; }

int hours(unsigned long epochSeconds) { return (epochSeconds / 3600) % 24; }

void WarsawTimeConverter::fromUtc(unsigned long utcEpochSeconds, int millis) {

  unsigned long localEpochSeconds = this->plTimezone->toLocal(utcEpochSeconds);

  sprintf(this->_warsawTime, "%02d:%02d:%02d.%03d", hours(localEpochSeconds),
          minutes(localEpochSeconds), seconds(localEpochSeconds), millis);
};

char *WarsawTimeConverter::formatted() { return this->_warsawTime; };
