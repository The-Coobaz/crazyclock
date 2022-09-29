#include <AUnit.h>
#include <Arduino.h>

#include "FakeTime.h"

test(should_correctly_return_hour_minutes_and_seconds) {
  // given
  FakeTime fakeTime = FakeTime(0, 1, 2);

  // then
  assertEqual(fakeTime.hour(), 0);
  assertEqual(fakeTime.minutes(), 1);
  assertEqual(fakeTime.seconds(), 2);
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
