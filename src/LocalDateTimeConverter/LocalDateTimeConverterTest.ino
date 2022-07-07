#include <AUnit.h>
#include <Arduino.h>

#include "LocalDateTimeConverter.h"

test(epoch_start_test) {
  // given
  LocalDateTimeConverter pl = LocalDateTimeConverter::PL;
  unsigned long epochStart = 0;
  unsigned long expected = 3600;

  // when
  unsigned long actual = pl.fromEpochSeconds(epochStart);

  // then
  assertEqual(actual, expected);
}

test(last_second_of_summer_time) {

  

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
