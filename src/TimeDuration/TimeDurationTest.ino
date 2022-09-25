#include <AUnit.h>
#include <Arduino.h>

#include "TimeDuration.h"

test(should_create_distance_from_zeros) {

  TimeDuration actual = TimeDuration::fromDistance(0L, 0L);

  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);
}

test(should_correctly_calculate_distance_from_same_values) {
  unsigned long newSecondObservedAt = 12345L;
  unsigned long distanceTo = 12345L;

  TimeDuration actual = TimeDuration::fromDistance(12345L, 12345L);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);

  actual = TimeDuration::fromDistance(-5L, -5L);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 0L);
}

test(should_correctly_calculate_less_than_second) {
  long from = 12345L;
  long to = from + 345;
  TimeDuration actual = TimeDuration::fromDistance(from, to);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 345L);
}

test(should_correctly_calculate_more_than_second) {
  long from = 987654321L;
  long to = from + 1234567890;
  TimeDuration actual = TimeDuration::fromDistance(from, to);
  assertEqual(actual.getSeconds(), 1234567L);
  assertEqual(actual.getMillis(), 890L);
}

test(should_correctly_calculate_when_millis_resets) {
  long from = (ARDUINO_MAX_MILLIS) - 300L;
  long to = 21L;

  TimeDuration actual = TimeDuration::fromDistance(from, to);
  assertEqual(actual.getSeconds(), 0L);
  assertEqual(actual.getMillis(), 321L);
}


test(should_correctly_calculate_duration_longer_than_second_when_millis_resets) {
  long from = (ARDUINO_MAX_MILLIS) - 300L;
  long to = 1234567890L;

  TimeDuration actual = TimeDuration::fromDistance(from, to);
  assertEqual(actual.getSeconds(), 1234568L);
  assertEqual(actual.getMillis(), 190L);
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
