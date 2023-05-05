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

test(should_calculate_millis_passed_over_month) {

  Time actual;
  unsigned long expectedSeconds;
  int expectedMillis;

  actual = calculatePassedTime(valentinesUTCSecond, 100,
                               valentinesUTCSecond + 3600 * 24 * 31, 100);
  expectedSeconds = 3600 * 24 * 31;
  expectedMillis = 0;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual = calculatePassedTime(valentinesUTCSecond, 101,
                               valentinesUTCSecond + 3600 * 24 * 31, 100);
  expectedSeconds = 3600 * 24 * 31 - 1;
  expectedMillis = 999;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);
}

test(should_correctly_calculate_with_scaling_factor_zero) {

  Time passedTime;
  double scalingFactor = 0.0;
  long long actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)0);
}

test(should_correctly_calculate_with_scaling_factor_one) {

  Time passedTime;
  double scalingFactor = 1.0;
  long long actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)123456);
}

test(should_correctly_calculate_with_scaling_factor_half) {

  Time passedTime;
  double scalingFactor = 0.5;
  long long actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)61728);
}

test(should_correctly_calculate_with_scaling_factor_one_third) {

  Time passedTime;
  double scalingFactor = 0.333333333333333333;
  long long actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)41152);

  passedTime.seconds = 2;
  passedTime.millis = 10;

  actual = scalePassedTime(passedTime, scalingFactor);
  // incorrect because of numeric reasons (should be 670)
  assertEqual(actual, (long long)669);
}

test(should_correctly_calculate_with_scaling_factor_one_eight) {

  Time passedTime;
  double scalingFactor = 0.125;
  long long actual;

  passedTime.seconds = 489;
  passedTime.millis = 400;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)61175);

  passedTime.seconds = 0;
  passedTime.millis = 128;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)16);
}

test(should_correctly_calculate_with_scaling_factor_nine) {

  Time passedTime;
  double scalingFactor = 9;
  long long actual;

  passedTime.seconds = 2;
  passedTime.millis = 873;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)25857);

  passedTime.seconds = 0;
  passedTime.millis = 128;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)1152);
}

test(should_correctly_calculate_with_scaling_factor_seventy_three) {

  Time passedTime;
  double scalingFactor = 73;
  long long actual;

  passedTime.seconds = 0;
  passedTime.millis = 136;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)9928);

  passedTime.seconds = 0;
  passedTime.millis = 128;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)9344);
}

test(should_correctly_calculate_with_scaling_factor_minus_three) {

  Time passedTime;
  double scalingFactor = -3;
  long long actual;

  passedTime.seconds = 0;
  passedTime.millis = 136;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)-408);

  passedTime.seconds = 0;
  passedTime.millis = 128;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)-384);
}

test(should_correctly_calculate_with_scaling_factor_minus_half) {

  Time passedTime;
  double scalingFactor = -0.5;
  long long actual;

  passedTime.seconds = 123;
  passedTime.millis = 456;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)-61728);

  passedTime.seconds = 0;
  passedTime.millis = 123;

  actual = scalePassedTime(passedTime, scalingFactor);
  // truncated instead of rounded (exact value: -61.5)
  assertEqual(actual, (long long)-61);
}

test(should_correctly_calculate_with_scaling_factor_minus_one_thousands) {

  Time passedTime;
  double scalingFactor = -0.001;
  long long actual;

  passedTime.seconds = 1;
  passedTime.millis = 010;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)-1);

  passedTime.seconds = 2;
  passedTime.millis = 222;

  actual = scalePassedTime(passedTime, scalingFactor);
  // truncated instead of rounded (exact value: -61.5)
  assertEqual(actual, (long long)-2);
}

test(should_correctly_calculate_with_scaling_factor_ninenty_nine) {

  Time passedTime;
  double scalingFactor = 99;
  long long actual;

  // check if it will work for longer time (one month)
  passedTime.seconds = 2628000;
  passedTime.millis = 10;

  actual = scalePassedTime(passedTime, scalingFactor);
  assertEqual(actual, (long long)260172000990);

  // one year
  passedTime.seconds = 31536000;
  passedTime.millis = 001;

  actual = scalePassedTime(passedTime, scalingFactor);
  // truncated instead of rounded (exact value: -61.5)
  assertEqual(actual, (long long)3122064000099);
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
