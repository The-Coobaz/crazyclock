#include <AUnit.h>
#include <Arduino.h>

#include "PassedTime.h"

test(should_create_distance_from_zeros) {

  PassedTime actual = PassedTime::fromDistance(0L, 0L);

  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);
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
