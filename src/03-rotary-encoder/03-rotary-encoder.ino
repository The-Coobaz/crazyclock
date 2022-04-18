#include <RotaryEncoder.h>
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd(0x27);
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

// https://github.com/mathertel/RotaryEncoder
RotaryEncoder encoder(12, 14, RotaryEncoder::LatchMode::TWO03);

int oldPosition = -999;
int newPosition = 0;

void setup() {
  int status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) {
    hd44780::fatalError(status); // does not return
  }

  lcd.clear();
  lcd.home();
  lcd.print("Basic Encoder Test");
}

void loop() {
  encoder.tick();
  newPosition = encoder.getPosition();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print(newPosition);
  }
}
