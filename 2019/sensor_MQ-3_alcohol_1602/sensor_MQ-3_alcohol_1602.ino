#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

int TIME_UNTIL_WARMUP = 10;
unsigned long time;

int analogPin = 0;
int val = 0;
int LED = 13;

void setup()
{
  Serial.begin(57600);  // start serial to PC
  pinMode(LED, OUTPUT); // for status LED
  lcd.begin(16, 2); // initialize LCD with number of columns and rows
}

void loop()
{
  delay(100);

  val = readAlcohol();
  printTitle();
  printWarming();

  time = millis()/1000;
  
  if(time<=TIME_UNTIL_WARMUP)
  {
    lcd.setCursor(13,1);
    lcd.print(TIME_UNTIL_WARMUP-time);
    lcd.print("  ");
  }else
  {
     printTitle();
     printAlcohol(val);
     printAlcoholLevel(val);  
  }
}

void printTitle()
{
  lcd.setCursor(0,0);
  lcd.print("MQ-3 Alcohol sen");  
}

void printWarming()
{
  lcd.setCursor(0,1);
  lcd.print("Warming up:");
  Serial.println("Warming up:");  
}

void printAlcohol(int value)
{
  lcd.setCursor(0,1);
  lcd.print(val);
}

void printAlcoholLevel(int value)
{
  lcd.setCursor(0,1);
  if(value<200)                 lcd.print("You are sober.  ");
  if (value>=200 && value<280)  lcd.print("You had a beer. ");
  if (value>=280 && value<350)  lcd.print("Two/more beers. ");
  if (value>=350 && value <450) lcd.print("I smell Oyzo!   ");
  if(value>450)                 lcd.print("You are drunk!  ");
  lcd.setCursor(13,0);
  lcd.print(value);
  lcd.print("  ");
}
 
int readAlcohol()
{
  int val = 0;
  int val1;
  int val2;
  int val3; 

  val1 = analogRead(analogPin); 
  delay(10);
  val2 = analogRead(analogPin); 
  delay(10);
  val3 = analogRead(analogPin);
  
  val = (val1+val2+val3)/3;
  return val;
}
