#include <AUnit.h>
#include <Arduino.h>

#include "FakeTime.h"

test(should_update_valid_times) {
  char formattedTimeBuffer[20] = "<initial value>";
  FakeTime tested = FakeTime();

  tested.setTime(12, 34, 56);
  tested.formatTime(formattedTimeBuffer);
  assertEqual(formattedTimeBuffer, "12:34:56");

  tested.setTime(0, 0, 0);
  tested.formatTime(formattedTimeBuffer);
  assertEqual(formattedTimeBuffer, "00:00:00");

  tested.setTime(6, 30, 0);
  tested.formatTime(formattedTimeBuffer);
  assertEqual(formattedTimeBuffer, "06:30:00");

  tested.setTime(0, 0, 1);
  tested.formatTime(formattedTimeBuffer);
  assertEqual(formattedTimeBuffer, "00:00:01");
}

test(should_handle_hours_errors_correctly_for_updates) {

  int status = SUCCESS;
  FakeTime tested = FakeTime();

  status = tested.setTime(-1, 34, 56);
  assertEqual(status, INCORRECT_HOUR);
}

test(should_handle_minutes_errors_correctly_for_updates) {

  int status = SUCCESS;
  FakeTime tested = FakeTime();

  status = tested.setTime(0, 60, 0);
  assertEqual(status, INCORRECT_MINUTE);
}

test(should_handle_seconds_errors_correctly_for_updates) {

  int status = SUCCESS;
  FakeTime tested = FakeTime();

  status = tested.setTime(6, 5, 65);
  assertEqual(status, INCORRECT_SECOND);
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
