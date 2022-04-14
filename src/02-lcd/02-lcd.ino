#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd(0x27);
// This ensures that each each lcd object is assigned to a specific
// lcd device rather than letting the library automatically asign it.

// LCD geometry
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

int customCharCode = 3;
uint8_t cross[8] = {0x00, 0x1b, 0x0e, 0x04, 0x0e, 0x1b, 0x00, 0x00};

void setup() {
  int status;

  // note:
  //	begin() will automatically turn on the backlight
  //
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) // non zero status means it was unsuccesful
  {
    // hd44780 has a fatalError() routine that blinks an led if possible
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }

  // initalization was successful, the backlight should be on now
  lcd.clear();
  lcd.home();
  lcd.print("Hello, World!");

  lcd.createChar(customCharCode, cross);
}

void loop() {
  for (uint8_t i = 0; i < 20; i++) {
    lcd.setCursor(i, 2);
    // lcd.print("*");
    lcd.write(customCharCode);
    delay(100);
  }
  for (uint8_t i = 0; i < 20; i++) {
    lcd.setCursor(i, 2);
    lcd.print(" ");
    delay(100);
  }
}
