#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // for I2C expander

hd44780_I2Cexp lcd; // declare lcd object:

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello world!");  
}

void loop() {
}
