#include <AUnitVerbose.h>
#include <Arduino.h>

#include "computeFakeTime.h"

// UTC seconds for 2022-02-14T12:34:56UTC
unsigned long valentinesUTCSecond = 1644842096ul;

test(should_calculate_simple_passed_millis) {

  Time actual;
  unsigned long expectedSeconds = 0ul;
  int expectedMillis;

  actual =
      calculatePassedTime(valentinesUTCSecond, 111, valentinesUTCSecond, 111);
  expectedMillis = 0;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual =
      calculatePassedTime(valentinesUTCSecond, 222, valentinesUTCSecond, 345);
  expectedMillis = 123;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual =
      calculatePassedTime(valentinesUTCSecond, 1, valentinesUTCSecond, 999);
  expectedMillis = 998;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);
}

test(should_calculate_when_start_millis_greater_than_current_millis) {

  Time actual;
  unsigned long expectedSeconds;
  int expectedMillis;

  actual =
      calculatePassedTime(valentinesUTCSecond, 999, valentinesUTCSecond + 1, 1);
  expectedSeconds = 0ul;
  expectedMillis = 2;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual = calculatePassedTime(valentinesUTCSecond, 500,
                               valentinesUTCSecond + 1, 499);
  expectedSeconds = 0ul;
  expectedMillis = 999;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);
}

test(should_calculate_millis_passed_over_seconds_change) {

  Time actual;
  unsigned long expectedSeconds;
  int expectedMillis;

  actual = calculatePassedTime(valentinesUTCSecond, 101,
                               valentinesUTCSecond + 4, 102);
  expectedSeconds = 4ul;
  expectedMillis = 1;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual = calculatePassedTime(valentinesUTCSecond, 101,
                               valentinesUTCSecond + 4, 100);
  expectedSeconds = 3ul;
  expectedMillis = 999;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);
}

test(should_correctly_calculate_with_scaling_factor_zero) {

  Time passedTime;
  double scalingFactor = 0.0;
  Time actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual.seconds, 0ul);
  assertEqual(actual.millis, 0);
}

test(should_correctly_calculate_with_scaling_factor_one) {

  Time passedTime;
  double scalingFactor = 1.0;
  Time actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual.seconds, 123ul);
  assertEqual(actual.millis, 456);
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
