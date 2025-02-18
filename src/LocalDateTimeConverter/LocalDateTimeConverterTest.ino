#include <AUnit.h>
#include <Arduino.h>

#include "LocalDateTimeConverter.h"

// UTC seconds for 2022-02-14T12:34:56UTC
unsigned long valentinesUTCSecond = 1644842096ul;

test(should_be_one_hour_later_in_PL_at_epoch_start) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochStart = 0;

  // when
  LocalDateTime localDateTime = pl.fromUtc(epochStart);

  // then
  assertEqual(localDateTime.getLocalSeconds(), epochStart + 3600);
}

test(should_recognize_same_time_on_valentines_day) {
  // given
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime valentinesInUTC = utc.fromUtc(valentinesUTCSecond);
  LocalDateTime valentinesInPL = pl.fromUtc(valentinesUTCSecond);

  // then
  assertEqual(valentinesInUTC.getLocalSeconds(), valentinesUTCSecond);
  assertEqual(valentinesInPL.getLocalSeconds(), valentinesUTCSecond + 3600);
}

test(should_correctly_show_UTC_time) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;

  // epoch start
  assertEqual(utc.fromUtc(0ul).getLocalSeconds(), 0ul);
  // 2020-02-29, 00:00:00 UTC
  assertEqual(utc.fromUtc(1582934400ul).getLocalSeconds(), 1582934400ul);
  // 2050-08-15, 17:15:00 UTC
  assertEqual(utc.fromUtc(2544196500ul).getLocalSeconds(), 2544196500ul);
  // 2100-08-15, 17:15:00 UTC
  assertEqual(utc.fromUtc(4122033300ul).getLocalSeconds(), 4122033300ul);

  // 15th of August 2200 -> number overflow?
  // assertEqual(utc.fromUtc(7277706900ul), 7277706900ul);
}

test(should_correctly_convert_to_PL_time) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // epoch start
  assertEqual(pl.fromUtc(0ul).getLocalSeconds(), 3600ul);
  // 2020-02-29, 00:00:00 UTC
  assertEqual(pl.fromUtc(1582934400ul).getLocalSeconds(), 1582934400ul + 3600);
  // 2050-08-15, 17:15:00 UTC
  assertEqual(pl.fromUtc(2544196500ul).getLocalSeconds(), 2544196500ul + 7200);
  // 2100-08-15, 17:15:00 UTC
  assertEqual(pl.fromUtc(4122033300ul).getLocalSeconds(), 4122033300ul + 7200);
}

// in March we change the clock from 2 AM to 3 AM
test(should_convert_PL_time_near_spring_time_change) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // 2020-01-29, 00:59:00 UTC
  unsigned long utcBefore = 1580259540ul;
  LocalDateTime beforePL = pl.fromUtc(utcBefore);
  // 2020-01-29, 01:01:00 UTC
  unsigned long utcAfter = 1580259660ul;
  LocalDateTime afterPL = pl.fromUtc(utcAfter);

  assertEqual(beforePL.getLocalSeconds(), utcBefore + 3600);
  assertEqual(afterPL.getLocalSeconds(), utcAfter + 7200);
}

// in October we change the clock from 3 AM to 2 AM
test(should_convert_PL_time_near_autumn_time_change) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // 2020-10-25, 00:59:00 UTC
  unsigned long utcBefore = 1603587540ul;
  LocalDateTime beforePL = pl.fromUtc(utcBefore);
  // 2020-10-25, 02:01:00 UTC
  unsigned long utcAfter = 1603587660ul;
  LocalDateTime afterPL = pl.fromUtc(utcAfter);

  assertEqual(beforePL.getLocalSeconds(), utcBefore + 7200);
  assertEqual(afterPL.getLocalSeconds(), utcAfter + 3600);
}

// in October we change the clock from 3 AM to 2 AM
test(should_convert_to_same_PL_time_twice_during_a_night) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // 2020-10-25, 00:00:30 UTC
  unsigned long utcFirst = 1603585800;
  LocalDateTime firstPL = pl.fromUtc(utcFirst);
  // 2020-10-25, 00:01:30 UTC
  unsigned long utcSecond = 1603589400;
  LocalDateTime secondPL = pl.fromUtc(utcSecond);

  // 2020-10-25, 00:02:30
  unsigned long expected = 1603593000;
  assertEqual(firstPL.getLocalSeconds(), expected);
  assertEqual(secondPL.getLocalSeconds(), expected);
}

// in October we change the clock from 3 AM to 2 AM
test(should_convert_with_time_fragments_near_autumn_time_change_2022) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // 2022-10-30, 00:00:00 UTC
  unsigned long utcMidnight = 1667088000;
  // 2022-10-30, 02:00:00 UTC
  unsigned long utcMidnightPlusTwoHours = utcMidnight + (2 * 3600);
  LocalDateTime tested = pl.fromUtc(utcMidnightPlusTwoHours);

  // Two hours later we should have 03:00:00 Warsaw time (CET +1)
  assertEqual(tested.getLocalTimeFragment(HOURS), 3);
  assertEqual(tested.getLocalTimeFragment(MINUTES), 0);
  assertEqual(tested.getLocalTimeFragment(SECONDS), 0);
}

test(should_return_time_fragments_at_epoch_start_UTC) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;

  // epoch start
  LocalDateTime utcEpochStart = utc.fromUtc(0ul);
  assertEqual(utcEpochStart.getLocalTimeFragment(HOURS), 0);
  assertEqual(utcEpochStart.getLocalTimeFragment(MINUTES), 0);
  assertEqual(utcEpochStart.getLocalTimeFragment(SECONDS), 0);
}

test(local_date_get_time_fragments_at_epoch_start_PL) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;

  // epoch start
  LocalDateTime plEpochStart = pl.fromUtc(0ul);
  assertEqual(plEpochStart.getLocalTimeFragment(HOURS), 1);
  assertEqual(plEpochStart.getLocalTimeFragment(MINUTES), 0);
  assertEqual(plEpochStart.getLocalTimeFragment(SECONDS), 0);
}

test(should_get_time_fragments_at_valentines_UTC) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTime valentines = utc.fromUtc(valentinesUTCSecond);

  assertEqual(valentines.getLocalTimeFragment(HOURS), 12);
  assertEqual(valentines.getLocalTimeFragment(MINUTES), 34);
  assertEqual(valentines.getLocalTimeFragment(SECONDS), 56);
}

test(should_get_time_fragments_at_valentines_pl) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime valentines = pl.fromUtc(valentinesUTCSecond);

  // noon in UTC on valentines day is 1 pm in Poland
  assertEqual(valentines.getLocalTimeFragment(HOURS), 13);
  assertEqual(valentines.getLocalTimeFragment(MINUTES), 34);
  assertEqual(valentines.getLocalTimeFragment(SECONDS), 56);
}

test(local_date_get_time_fragments_utc_increased_seconds) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTime original = utc.fromUtc(valentinesUTCSecond);
  LocalDateTime increased = utc.fromUtc(valentinesUTCSecond + 1);

  assertEqual(original.getLocalTimeFragment(SECONDS) + 1,
              increased.getLocalTimeFragment(SECONDS));
}

test(local_date_get_time_fragments_utc_increased_minutes) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTime original = utc.fromUtc(valentinesUTCSecond);
  LocalDateTime increased = utc.fromUtc(valentinesUTCSecond + 60);

  assertEqual(original.getLocalTimeFragment(MINUTES) + 1,
              increased.getLocalTimeFragment(MINUTES));
}

test(local_date_get_time_fragments_utc_increased_hours) {
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;
  LocalDateTime original = utc.fromUtc(valentinesUTCSecond);
  LocalDateTime increased = utc.fromUtc(valentinesUTCSecond + 3600);

  assertEqual(original.getLocalTimeFragment(HOURS) + 1,
              increased.getLocalTimeFragment(HOURS));
}

test(local_date_get_time_fragments_pl_increased_seconds) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime original = pl.fromUtc(valentinesUTCSecond);
  LocalDateTime increased = pl.fromUtc(valentinesUTCSecond + 1);

  assertEqual(original.getLocalTimeFragment(SECONDS) + 1,
              increased.getLocalTimeFragment(SECONDS));
}

test(local_date_get_time_fragments_pl_increased_minutes) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime original = pl.fromUtc(valentinesUTCSecond);
  LocalDateTime increased = pl.fromUtc(valentinesUTCSecond + 60);

  assertEqual(original.getLocalTimeFragment(MINUTES) + 1,
              increased.getLocalTimeFragment(MINUTES));
}

test(local_date_get_time_fragments_pl_increased_hours) {
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  LocalDateTime original = pl.fromUtc(valentinesUTCSecond);
  LocalDateTime increased = pl.fromUtc(valentinesUTCSecond + 3600);

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
