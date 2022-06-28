#line 2 "basic.ino"

// Adapted from:
// https://github.com/mmurdoch/arduinounit/blob/master/examples/basic/basic.ino

#include <AUnit.h>

test(correct) {
  int x = 1;
  assertEqual(x, 1);
}

// test(incorrect) {
//   int x = 1;
//   assertNotEqual(x, 1);
// }

//----------------------------------------------------------------------------
// setup() and loop()
//----------------------------------------------------------------------------

void setup() {
  delay(1000); // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ; // for the Arduino Leonardo/Micro only

  Serial.println(F("This line will appear in console"));
}

void loop() { aunit::TestRunner::run(); }
