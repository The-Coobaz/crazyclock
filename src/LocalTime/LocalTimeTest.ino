#include <Arduino.h>
#include <AUnit.h>

#include "LocalTime.h"

test(dummy_unit_test) {
  LocalTime localTime;
  unsigned long actual = localTime.fromEpochSeconds(0);
  assertEqual(actual, 0UL);
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
