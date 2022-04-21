#line 2 "FakeTime.ino"

#include "../../crazyclock/FakeTime/FakeTime.h"
#include <AUnit.h>

// To run tests please: `export ARDUINO_LIB_DIRS=${HOME}/Arduino/libraries`

test(correct) {
  FakeTime fakeTime(0L);
  long fakeMillis = fakeTime.getFakeMillis(0);
  assertEqual(fakeMillis, 0L);
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
