#include <AUnit.h>
#include <Arduino.h>

#include <Time.h>

#include "LocalDateTimeConverter.h"

test(epoch_start_test) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochStart = 0;

  // when
  LocalDateTime localDateTime = pl.fromUtc(epochStart);

  // then
  assertEqual(localDateTime.getEpochSeconds(), epochStart);
  assertEqual(localDateTime.getLocalSeconds(), epochStart + 3600);
}

test(valentines_day) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime valentines = pl.fromUtc(2022, 2, 14, 12, 34, 56);
  unsigned long expectedEpochSeconds = 1644842096ul;

  // then
  assertEqual(valentines.getEpochSeconds(), expectedEpochSeconds);
}

test(utc_conversion_to_seconds) {
  // given
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;

  assertEqual(utc.fromUtc(2022, 2, 14, 12, 34, 56).getEpochSeconds(), 1644842096ul);
  assertEqual(utc.fromUtc(2022, 2, 14, 12, 34, 56).getLocalSeconds(), 1644842096ul);
  assertEqual(utc.fromUtc(2020, 2, 29, 0, 0, 0).getEpochSeconds(), 1582934400ul);
  assertEqual(utc.fromUtc(2020, 2, 29, 0, 0, 0).getLocalSeconds(), 1582934400ul);
  assertEqual(utc.fromUtc(2050, 8, 15, 17, 15, 0).getEpochSeconds(), 2544196500ul);
  assertEqual(utc.fromUtc(2050, 8, 15, 17, 15, 0).getLocalSeconds(), 2544196500ul);
  assertEqual(utc.fromUtc(2100, 8, 15, 17, 15, 0).getEpochSeconds(), 4122033300ul);
  assertEqual(utc.fromUtc(2100, 8, 15, 17, 15, 0).getLocalSeconds(), 4122033300ul);

  // 15th of August 2200
  // number overflow?
  //assertEqual(utc.fromUtc(2200, 8, 15, 17, 15, 0), 7277706900ul);
}

test(pl_conversion_to_seconds) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // epoch start
  assertEqual(pl.fromUtc(0ul).getLocalSeconds(), 3600ul);

  assertEqual(pl.fromUtc(2022, 2, 14, 12, 34, 56).getEpochSeconds(), 1644842096ul);
  assertEqual(pl.fromUtc(2022, 2, 14, 12, 34, 56).getLocalSeconds(), 1644842096ul + 3600);
  assertEqual(pl.fromUtc(2020, 2, 29, 0, 0, 0).getEpochSeconds(), 1582934400ul);
  assertEqual(pl.fromUtc(2020, 2, 29, 0, 0, 0).getLocalSeconds(), 1582934400ul + 3600);
  assertEqual(pl.fromUtc(2050, 8, 15, 17, 15, 0).getEpochSeconds(), 2544196500ul);
  assertEqual(pl.fromUtc(2050, 8, 15, 17, 15, 0).getLocalSeconds(), 2544196500ul + 7200);
  assertEqual(pl.fromUtc(2100, 8, 15, 17, 15, 0).getEpochSeconds(), 4122033300ul);
  assertEqual(pl.fromUtc(2100, 8, 15, 17, 15, 0).getLocalSeconds(), 4122033300ul + 7200);
}

// in Spring we change the clock from 2 AM to 3 AM
test(pl_conversion_near_spring_time_change_2020) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // before 1 AM UTC (before 2 AM CET)
  LocalDateTime before = pl.fromUtc(2020, 3, 29, 0, 59, 0);
  assertEqual(before.getLocalSeconds(), before.getEpochSeconds() + 3600);
  // after 1 AM UTC (after 3 AM CET)
  LocalDateTime after = pl.fromUtc(2020, 3, 29, 1, 1, 0);
  assertEqual(after.getLocalSeconds(), after.getEpochSeconds() + 7200);
}

// in Spring we change the clock from 2 AM to 3 AM
test(pl_conversion_near_autumn_time_change_2020) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // before 1 AM UTC (before 3 AM CEST)
  LocalDateTime before = pl.fromUtc(2020, 10, 25, 0, 59, 0);
  assertEqual(before.getLocalSeconds(), before.getEpochSeconds() + 7200);
  // after 1 AM UTC (after 2 AM CEST)
  LocalDateTime after = pl.fromUtc(2020, 10, 25, 1, 1, 0);
  assertEqual(after.getLocalSeconds(), after.getEpochSeconds() + 3600);
}

//----------------------------------------------------------------------------
// setup() and loop()
//----------------------------------------------------------------------------

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ; // for the Arduino Leonardo/Micro only
}

void loop() { aunit::TestRunner::run(); }
