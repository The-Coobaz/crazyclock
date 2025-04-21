#include <AUnit.h>
#include <Arduino.h>

#include "WarsawTimeConverter.h"

test(should_be_two_hours_later_in_PL_at_epoch_start) {
  // given
  WarsawTimeConverter converter = WarsawTimeConverter();
  char *formatted = converter.formatted();
  // and
  // DST has been in use in Poland since 1977;
  unsigned long utcEpochStart = 0ul;
  String expected = "02:00:00.000";

  // when
  converter.fromUtc(utcEpochStart, 0);

  // then
  assertEqual(formatted, expected);
}

test(should_convert_valentines_day) {
  // given
  WarsawTimeConverter converter = WarsawTimeConverter();
  char *formatted = converter.formatted();
  // UTC seconds for 2022-02-14T12:34:56UTC
  unsigned long valentinesUTCSecond = 1644842096;
  String expected = "13:34:56.000";

  // when
  converter.fromUtc(valentinesUTCSecond, 0);

  // then
  assertEqual(formatted, expected);
}

test(should_correctly_convert_to_PL_time) {
  WarsawTimeConverter converter = WarsawTimeConverter();
  char *formatted = converter.formatted();
  String expected;

  // 2020-02-29, 00:00:00 UTC
  converter.fromUtc(1582934400ul, 0);
  expected = "01:00:00.000";
  assertEqual(formatted, expected);

  // 2050-08-15, 17:15:02 UTC
  converter.fromUtc(2544196502ul, 0);
  expected = "19:15:02.000";
  assertEqual(formatted, expected);

  // 2100-08-15, 17:15:00 UTC
  converter.fromUtc(4122033300ul, 543);
  expected = "19:15:00.543";
  assertEqual(formatted, expected);
}

// in March we change the clock from 2 AM to 3 AM
test(should_convert_PL_time_near_spring_time_change) {
  // given
  WarsawTimeConverter converter = WarsawTimeConverter();
  char *formatted = converter.formatted();

  // 2020-03-29, 00:59:59 UTC
  unsigned long utcBefore = 1585443599;
  converter.fromUtc(utcBefore, 999);
  String expectedBefore = "01:59:59.999";
  assertEqual(formatted, expectedBefore);

  // 2020-03-29, 01:00:00 UTC
  unsigned long utcAfter = 1585443600;
  converter.fromUtc(utcAfter, 0);
  String expectedAfter = "03:00:00.000";
  assertEqual(formatted, expectedAfter);
}

// in October we change the clock from 3 AM to 2 AM
test(should_convert_PL_time_near_autumn_time_change) {
  // given
  WarsawTimeConverter converter = WarsawTimeConverter();
  char *formatted = converter.formatted();

  // 2020-10-25, 00:59:59 UTC
  unsigned long utcBefore = 1603587599;
  converter.fromUtc(utcBefore, 999);
  String expectedBefore = "02:59:59.999";
  assertEqual(formatted, expectedBefore);

  // 2020-10-25, 01:00:00 UTC
  unsigned long utcAfter = 1603587600;
  converter.fromUtc(utcAfter, 0);
  String expectedAfter = "02:00:00.000";
  assertEqual(formatted, expectedAfter);
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
