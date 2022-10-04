#include <AUnit.h>
#include <Arduino.h>

#include "FakeTime.h"

test(should_correctly_return_hour_minutes_and_seconds) {
  // given
  FakeTime fakeTime = FakeTime(0, 1, 2);

  // when
  FakeTime actual = fakeTime.plusMillis(999);

  // then
  assertEqual(actual.hour(), 0);
  assertEqual(actual.minutes(), 1);
  assertEqual(actual.seconds(), 2);
}

test(should_correctly_add_second_and_a_half) {
  // given
  FakeTime fakeTime = FakeTime(0, 1, 2);

  // when
  FakeTime actual = fakeTime.plusMillis(1500);

  // then
  assertEqual(actual.hour(), 0);
  assertEqual(actual.minutes(), 1);
  assertEqual(actual.seconds(), 3);
}

test(should_calculate_new_fake_time) {
  // given
  FakeTime fakeTime = FakeTime(17, 00, 00);

  // when
  int plusSeconds = 12;
  FakeTime actual = fakeTime.plusMillis(plusSeconds * 1000);

  // then
  assertEqual(actual.hour(), 17);
  assertEqual(actual.minutes(), 0);
  assertEqual(actual.seconds(), 12);
}

test(should_calculate_new_fake_time_overflow_minutes) {
  // given
  FakeTime fakeTime = FakeTime(17, 00, 00);

  // when
  int plusSeconds = 333;
  FakeTime actual = fakeTime.plusMillis(plusSeconds * 1000);

  // then
  assertEqual(actual.minutes(), 5);
  assertEqual(actual.seconds(), 33);
}

test(should_calculate_new_fake_time_overflow_hours) {
  // given
  FakeTime fakeTime = FakeTime(17, 00, 00);

  // when
  int plusSeconds = 3600;
  FakeTime actual = fakeTime.plusMillis(plusSeconds * 1000);

  // then
  assertEqual(actual.hour(), 18);
  assertEqual(actual.minutes(), 0);
  assertEqual(actual.seconds(), 0);
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
