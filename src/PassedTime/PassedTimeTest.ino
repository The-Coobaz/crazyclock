#include <AUnit.h>
#include <Arduino.h>

#include "PassedTime.h"

test(should_create_distance_from_zeros) {

  PassedTime actual = PassedTime::fromDistance(0L, 0L);

  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);
}

test(should_correctly_calculate_distance_from_same_values) {

  PassedTime actual = PassedTime::fromDistance(12345L, 12345L);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);

  actual = PassedTime::fromDistance(-5L, -5L);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);
}

test(should_correctly_calculate_less_than_second) {
  long from = 12345L;
  long to = from + 345;
  PassedTime actual = PassedTime::fromDistance(from, to);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 345L);
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
