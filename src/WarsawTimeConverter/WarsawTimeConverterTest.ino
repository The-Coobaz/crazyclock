#include <AUnit.h>
#include <Arduino.h>

#include "WarsawTimeConverter.h"

test(should_be_one_hour_later_in_PL_at_epoch_start) {
  // given
  WarsawTimeConverter converter = WarsawTimeConverter();
  unsigned long epochStart = 0;
  int millisZero = 0;
  String expected = "01:00:00.000";

  // when
  char *actual = converter.toWarsawTime(epochStart, millisZero);

  // then
  assertEqual(actual, expected);
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
