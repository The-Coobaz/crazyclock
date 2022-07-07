#include <AUnit.h>
#include <Arduino.h>

#include <Time.h>

#include "LocalDateTimeConverter.h"

unsigned long convert(int year, int month, int day, int hour, int minute,
                      int second) {
  tmElements_t tmElements;
  tmElements.Year = year - 1970;
  tmElements.Month = month;
  tmElements.Day = day;
  tmElements.Hour = hour;
  tmElements.Minute = minute;
  tmElements.Second = second;
  return makeTime(tmElements);
}

test(epoch_start_test) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochStart = 0;
  unsigned long expected = 3600;

  // when
  unsigned long actual = pl.fromUtc(epochStart);

  // then
  assertEqual(actual, expected);
}

test(valentines_day) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long utcTime = convert(2022, 2, 14, 12, 34, 56);
  unsigned long expectedPLTime = convert(2022, 2, 14, 13, 34, 56);

  // when
  unsigned long actual = pl.fromUtc(utcTime);

  // then
  assertEqual(actual, expectedPLTime);
}

test(test_function_for_conversion) {
  // epoch start
  assertEqual(0000000000ul, convert(1970, 1, 1, 0, 0, 0));
  // valentines day
  assertEqual(1644842096ul, convert(2022, 2, 14, 12, 34, 56));
  // 29th of February 2020
  assertEqual(1582934400ul, convert(2020, 2, 29, 0, 0, 0));
  // 15th of August 2050
  assertEqual(2544196500ul, convert(2050, 8, 15, 17, 15, 0));
  // 15th of August 2100
  assertEqual(4122033300ul, convert(2100, 8, 15, 17, 15, 0));
  // 15th of August 2200
  //assertEqual(7277706900ul, convert(2200, 8, 15, 17, 15, 0));
}

test(utc_conversion) {
  // given
  LocalDateTimeConverter utc = LocalDateTimeConverter::UTC;

  // epoch start
  assertEqual(utc.fromUtc(0000000000ul), convert(1970, 1, 1, 0, 0, 0));
  // valentines day
  assertEqual(utc.fromUtc(1644842096ul), convert(2022, 2, 14, 12, 34, 56));
  // 29th of February 2020
  assertEqual(utc.fromUtc(1582934400ul), convert(2020, 2, 29, 0, 0, 0));
  // 15th of August 2050
  assertEqual(utc.fromUtc(2544196500ul), convert(2050, 8, 15, 17, 15, 0));
  // 15th of August 2100
  assertEqual(utc.fromUtc(4122033300ul), convert(2100, 8, 15, 17, 15, 0));
  // 15th of August 2200
  //assertEqual(utc.fromUtc(7277706900ul), convert(2200, 8, 15, 17, 15, 0));
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
