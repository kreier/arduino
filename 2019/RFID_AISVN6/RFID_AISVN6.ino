#include <SoftwareSerial.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

SoftwareSerial RFID(2, 3); // RX and TX

int data1 = 0;
int ok = -1;
int LED = 13;
int y = 0;
int block = 255;
unsigned long time;
int days = 0;
int hours = 0;
int minutes = 0;
boolean show_uptime = false;

int tag1[14] = {2,48,49,48,70,65,66,49,70,52,50,70,55,3};
int newtag[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // used for read comparisons

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

void setup()
{
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC
  pinMode(LED, OUTPUT); // for status LED
  time = millis();
  // initialize LCD with number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD
  lcd.print("Hello AIS World!");
  lcd.setCursor(0,0);
  delay(1000);
  lcd.print("Place your IDtag");
}

boolean comparetag(int aa[14], int bb[14])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 14 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 14)
  {
    ff = true;
  }
  return ff;
}

void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (comparetag(newtag, tag1) == true)
  {
    ok++;
  }
}

void readTags()
{
  ok = -1;

  if (RFID.available() > 0) 
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.

    for (int z = 0 ; z < 14 ; z++) // read the rest of the tag
    {
      data1 = RFID.read();
      newtag[z] = data1;
    }
    RFID.flush(); // stops multiple reads

    // do the tags match up?
    checkmytags();
  }

  // now do something based on tag type
  if (ok > 0) // if we had a match
  {
    Serial.println("Accepted");
    digitalWrite(LED, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("  Master of the ");
    lcd.setCursor(0, 1);
    lcd.print("    MakerSpace  ");        
    delay(2000);
    digitalWrite(LED, LOW);
    lcd.setCursor(0,0);
    lcd.print("Place your IDtag");
    RFID.flush(); // stops multiple reads    
    ok = -1;
  }
  else if (ok == 0) // if we didn't have a match
  {
    Serial.println("Rejected");
    lcd.setCursor(0, 0);    
    for (int z = 1 ; z < 14 ; z++) // print card id
    {
      lcd.print(newtag[z]);
      lcd.print(" ");
      if(z == 6) lcd.setCursor(0, 1);
    }
    for (int z = 0 ; z < 50 ; z++) // blink for 5 seconds
    {
         digitalWrite(LED, HIGH);
         delay(50);
         digitalWrite(LED, LOW);
         delay(50);
    }           
    lcd.setCursor(0,0);
    lcd.print("Place your IDtag");
    RFID.flush(); // stops multiple reads
    ok = -1;
  }
}

void progressbar() {
  lcd.setCursor(y, 1);
  lcd.write(block);
  y++;
  if( y > 15 ) {
    y = 0 ;
    if (block == 255) {
      block = 160;
    }
    else {
      block = 255;
    }
  }
}

void uptime() {
  if( millis() - time > 60000 ) { // a minute has passed!
    time = millis();
    minutes++;
    if( minutes > 60) {
      minutes = 0;
      hours++;
    }
    if( hours > 24) {
      hours = 0;
      days++;
    }
    lcd.setCursor(0, 0);
    lcd.print("up ");
    lcd.print(days);
    lcd.print("d ");
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("min   ");
    show_uptime = true;
  }
  if( millis() - time < 0 ) { // rollover happened after unsigned long 4294967295 milliseconds = 49.71 days
    time = millis();
  }
  if(( millis() - time > 2500 ) && show_uptime == true) { // uptime shown for 1.5 seconds
    show_uptime = false;
    lcd.setCursor(0,0);
    lcd.print("Place your IDtag");
  }
}

void loop()
{
  readTags();
  progressbar();
  uptime();
  delay(100);
}
