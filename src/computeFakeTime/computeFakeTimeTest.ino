#include <AUnitVerbose.h>
#include <Arduino.h>

#include "computeFakeTime.h"

// UTC seconds for 2022-02-14T12:34:56UTC
unsigned long valentinesUTCSecond = 1644842096ul;

test(should_not_change_the_value_if_scaling_factor_is_zero) {

  double timeStoppedScalingFactor = 0.0;
  Fake actual;

  actual = computeFakeTime(valentinesUTCSecond, 123, 1644843210, 789,
                           timeStoppedScalingFactor);
  // the returned time should be same as input
  assertEqual(actual.epochSeconds, valentinesUTCSecond);
  assertEqual(actual.millis, 123);
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
