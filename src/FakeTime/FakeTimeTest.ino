#include <AUnit.h>
#include <Arduino.h>

#include "FakeTime.h"

test(should_convert_valid_times) {

  char formattedTimeBuffer[20] = "<initial value>";
  int status = FakeTime(12, 34, 56).formatTime(formattedTimeBuffer);
  assertEqual(status, SUCCESS);
  assertEqual(formattedTimeBuffer, "12:34:56");

  status = FakeTime(0, 0, 0).formatTime(formattedTimeBuffer);
  assertEqual(status, SUCCESS);
  assertEqual(formattedTimeBuffer, "00:00:00");

  status = FakeTime(6, 30, 0).formatTime(formattedTimeBuffer);
  assertEqual(status, SUCCESS);
  assertEqual(formattedTimeBuffer, "06:30:00");

  status = FakeTime(0, 0, 1).formatTime(formattedTimeBuffer);
  assertEqual(status, SUCCESS);
  assertEqual(formattedTimeBuffer, "00:00:01");
}

test(should_handle_hours_errors_correctly) {

  int status = SUCCESS;
  char formattedTimeBuffer[20] = "<initial value>";

  status = FakeTime(-1, 34, 56).formatTime(formattedTimeBuffer);
  assertEqual(status, INCORRECT_HOUR);
  assertEqual(formattedTimeBuffer, "<initial value>");
}

test(should_handle_minutes_errors_correctly) {

  int status = SUCCESS;
  char formattedTimeBuffer[20] = "<initial value>";

  status = FakeTime(0, 60, 0).formatTime(formattedTimeBuffer);
  assertEqual(status, INCORRECT_MINUTE);
  assertEqual(formattedTimeBuffer, "<initial value>");
}

test(should_handle_seconds_errors_correctly) {

  int status = SUCCESS;
  char formattedTimeBuffer[20] = "<initial value>";

  status = FakeTime(6, 5, 65).formatTime(formattedTimeBuffer);
  assertEqual(status, INCORRECT_SECOND);
  assertEqual(formattedTimeBuffer, "<initial value>");
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
