#include <AUnit.h>
#include <Arduino.h>

#include "TimeFormatter.h"

test(should_convert_valid_times) {

    char actual[] = "00:00:00";

    formatTime(12,34,56, actual);
    assertEqual(actual, "12:34:56");
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
