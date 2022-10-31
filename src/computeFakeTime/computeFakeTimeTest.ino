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
      calculateTimePassed(valentinesUTCSecond, 111, valentinesUTCSecond, 111);
  expectedMillis = 0;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual =
      calculateTimePassed(valentinesUTCSecond, 222, valentinesUTCSecond, 345);
  expectedMillis = 123;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);

  actual =
      calculateTimePassed(valentinesUTCSecond, 1, valentinesUTCSecond, 999);
  expectedMillis = 998;
  assertEqual(actual.seconds, expectedSeconds);
  assertEqual(actual.millis, expectedMillis);
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
