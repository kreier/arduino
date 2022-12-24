#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){        // usually I2C on D1 and D2, but used for motor driver
  Wire.begin(12,14); // I2C on D6/GPIO12/SDA and D5/GPIO14/SCL
  lcd.init();
  lcd.backlight();
  pinMode(16, OUTPUT);
}

void loop(){
  for(int i = 0; i < 2; i++){
    lcd.setCursor(0, i);
    lcd.print("Hello, World!");
    digitalWrite(16, i);
    delay(500);
    lcd.clear();
  }
}
