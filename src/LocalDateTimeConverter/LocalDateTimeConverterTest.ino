#include <AUnit.h>
#include <Arduino.h>

#include "LocalDateTimeConverter.h"

// UTC seconds for 2022-02-14T12:34:56UTC
unsigned long valentinesUTCSecond = 1644842096ul;

test(epoch_start_test) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochStart = 0;

  // when
  LocalDateTime localDateTime = pl.fromUtc(epochStart);

  // then
  assertEqual(localDateTime.getLocalSeconds(), epochStart + 3600);
}

test(valentines_day) {
  // given
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime valentinesInUTC = utc.fromUtc(2022, 2, 14, 12, 34, 56);
  LocalDateTime valentinesInPL = pl.fromUtc(2022, 2, 14, 12, 34, 56);

  // then
  assertEqual(valentinesInUTC.getLocalSeconds(), valentinesUTCSecond);
  assertEqual(valentinesInPL.getLocalSeconds(), valentinesUTCSecond + 3600);
}

test(utc_conversion_to_seconds) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;

  assertEqual(utc.fromUtc(2022, 2, 14, 12, 34, 56).getLocalSeconds(),
              valentinesUTCSecond);
  assertEqual(utc.fromUtc(2020, 2, 29, 0, 0, 0).getLocalSeconds(),
              1582934400ul);
  assertEqual(utc.fromUtc(2050, 8, 15, 17, 15, 0).getLocalSeconds(),
              2544196500ul);
  assertEqual(utc.fromUtc(2100, 8, 15, 17, 15, 0).getLocalSeconds(),
              4122033300ul);

  // 15th of August 2200
  // number overflow?
  // assertEqual(utc.fromUtc(2200, 8, 15, 17, 15, 0), 7277706900ul);
}

test(pl_conversion_to_seconds) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // epoch start
  assertEqual(pl.fromUtc(0ul).getLocalSeconds(), 3600ul);

  assertEqual(pl.fromUtc(2022, 2, 14, 12, 34, 56).getLocalSeconds(),
              valentinesUTCSecond + 3600);
  assertEqual(pl.fromUtc(2020, 2, 29, 0, 0, 0).getLocalSeconds(),
              1582934400ul + 3600);
  assertEqual(pl.fromUtc(2050, 8, 15, 17, 15, 0).getLocalSeconds(),
              2544196500ul + 7200);
  assertEqual(pl.fromUtc(2100, 8, 15, 17, 15, 0).getLocalSeconds(),
              4122033300ul + 7200);
}

// in March we change the clock from 2 AM to 3 AM
test(pl_conversion_near_spring_time_change_2020) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // local time before 1 AM UTC (before 2 AM CET)
  LocalDateTime beforeUTC = utc.fromUtc(2020, 3, 29, 0, 59, 0);
  LocalDateTime beforePL = pl.fromUtc(2020, 3, 29, 0, 59, 0);

  assertEqual(beforePL.getLocalSeconds(), beforeUTC.getLocalSeconds() + 3600);
  // local time after 1 AM UTC (after 3 AM CET)
  LocalDateTime afterUTC = utc.fromUtc(2020, 3, 29, 1, 1, 0);
  LocalDateTime afterPL = pl.fromUtc(2020, 3, 29, 1, 1, 0);
  assertEqual(afterPL.getLocalSeconds(), afterUTC.getLocalSeconds() + 7200);
}

// in October we change the clock from 3 AM to 2 AM
test(pl_conversion_near_autumn_time_change_2020) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // local time before 1 AM UTC (before 3 AM CEST)
  LocalDateTime beforeUTC = utc.fromUtc(2020, 10, 25, 0, 59, 0);
  LocalDateTime beforePL = pl.fromUtc(2020, 10, 25, 0, 59, 0);
  assertEqual(beforePL.getLocalSeconds(), beforeUTC.getLocalSeconds() + 7200);
  // local time after 1 AM UTC (after 2 AM CEST)
  LocalDateTime afterUTC = utc.fromUtc(2020, 10, 25, 1, 1, 0);
  LocalDateTime afterPL = pl.fromUtc(2020, 10, 25, 1, 1, 0);
  assertEqual(afterPL.getLocalSeconds(), afterUTC.getLocalSeconds() + 3600);
}

// in October we change the clock from 3 AM to 2 AM
test(pl_time_increase_near_autumn_time_change_2022) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // 2022-10-30, 00:00:00 UTC
  // 2022-10-30, 02:00:00 Warsaw time (CEST +2)
  unsigned long zero = 1667088000;

  unsigned long zeroPlusTwoHours = zero + (2 * 3600);
  LocalDateTime tested = pl.fromUtc(zeroPlusTwoHours);
  
  // Two hours later we should have 03:00:00 Warsaw time (CET +1)
  assertEqual(tested.getLocalTimeFragment(HOURS), 3);
  assertEqual(tested.getLocalTimeFragment(MINUTES), 0);
  assertEqual(tested.getLocalTimeFragment(SECONDS), 0);
}

test(local_date_get_time_fragments_at_epoch_start_utc) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;

  // epoch start
  LocalDateTime utcEpochStart = utc.fromUtc(0ul);
  assertEqual(utcEpochStart.getLocalTimeFragment(HOURS), 0);
  assertEqual(utcEpochStart.getLocalTimeFragment(MINUTES), 0);
  assertEqual(utcEpochStart.getLocalTimeFragment(SECONDS), 0);
}

test(local_date_get_time_fragments_at_epoch_start_pl) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // epoch start
  LocalDateTime plEpochStart = pl.fromUtc(0ul);
  assertEqual(plEpochStart.getLocalTimeFragment(HOURS), 1);
  assertEqual(plEpochStart.getLocalTimeFragment(MINUTES), 0);
  assertEqual(plEpochStart.getLocalTimeFragment(SECONDS), 0);
}

test(local_date_get_time_fragments_at_valentines_utc) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTime valentines = utc.fromUtc(2022, 2, 14, 12, 34, 56);

  assertEqual(valentines.getLocalTimeFragment(HOURS), 12);
  assertEqual(valentines.getLocalTimeFragment(MINUTES), 34);
  assertEqual(valentines.getLocalTimeFragment(SECONDS), 56);
}

test(local_date_get_time_fragments_at_valentines_pl) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime valentines = pl.fromUtc(2022, 2, 14, 12, 34, 56);

  // noon in UTC on valentines day is 1 pm in Poland
  assertEqual(valentines.getLocalTimeFragment(HOURS), 13);
  assertEqual(valentines.getLocalTimeFragment(MINUTES), 34);
  assertEqual(valentines.getLocalTimeFragment(SECONDS), 56);
}

test(local_date_get_time_fragments_utc_increased_seconds) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  unsigned long epochSeconds = 9876543210;
  LocalDateTime original = utc.fromUtc(epochSeconds);
  LocalDateTime increased = utc.fromUtc(epochSeconds + 1);

  assertEqual(original.getLocalTimeFragment(SECONDS) + 1,
              increased.getLocalTimeFragment(SECONDS));
}

test(local_date_get_time_fragments_utc_increased_minutes) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  unsigned long epochSeconds = 9876543210;
  LocalDateTime original = utc.fromUtc(epochSeconds);
  LocalDateTime increased = utc.fromUtc(epochSeconds + 60);

  assertEqual(original.getLocalTimeFragment(MINUTES) + 1,
              increased.getLocalTimeFragment(MINUTES));
}

test(local_date_get_time_fragments_utc_increased_hours) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  unsigned long epochSeconds = 9876543210;
  LocalDateTime original = utc.fromUtc(epochSeconds);
  LocalDateTime increased = utc.fromUtc(epochSeconds + 3600);

  assertEqual(original.getLocalTimeFragment(HOURS) + 1,
              increased.getLocalTimeFragment(HOURS));
}

test(local_date_get_time_fragments_pl_increased_seconds) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochSeconds = 9876543210;
  LocalDateTime original = pl.fromUtc(epochSeconds);
  LocalDateTime increased = pl.fromUtc(epochSeconds + 1);

  assertEqual(original.getLocalTimeFragment(SECONDS) + 1,
              increased.getLocalTimeFragment(SECONDS));
}

test(local_date_get_time_fragments_pl_increased_minutes) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochSeconds = 9876543210;
  LocalDateTime original = pl.fromUtc(epochSeconds);
  LocalDateTime increased = pl.fromUtc(epochSeconds + 60);

  assertEqual(original.getLocalTimeFragment(MINUTES) + 1,
              increased.getLocalTimeFragment(MINUTES));
}

test(local_date_get_time_fragments_pl_increased_hours) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochSeconds = 9876543210;
  LocalDateTime original = pl.fromUtc(epochSeconds);
  LocalDateTime increased = pl.fromUtc(epochSeconds + 3600);

  assertEqual(original.getLocalTimeFragment(HOURS) + 1,
              increased.getLocalTimeFragment(HOURS));
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
