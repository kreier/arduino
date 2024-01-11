/* Read iBUS */
// LORA915:        2   and ESP8266 NodeMCU, D1 R32 (Arduino size), DOIT ESP32 DEVKIT V1

#include <SoftwareSerial.h>

int ledPin = 2;
int rxPin = 15;
bool light = HIGH;    // LORA915, T-Koala, T8, Arduino
//bool light = LOW;   // WEMOS Lite, ESP8266 NODEMCU
bool dark  = !light;
int count = 0;
byte daten = 0;
SoftwareSerial iBus(rxPin, 4, 1); // RX, TX

void setup() {
  pinMode(ledPin, OUTPUT);
//  pinMode(rxPin,  INPUT);
  Serial.begin(115200);
  Serial.println("Let's start!");
  iBus.begin(100000);
}

void loop() {
//  daten = digitalRead(rxPin);
//  Serial.print(daten);
//  count++;
  if (iBus.available()) {
    daten = iBus.read();
    if(daten == 0x8E) {
//      Serial.println(".");
      Serial.print(daten, HEX);
      Serial.print("."); 
      count++;     
    }
    else {
      Serial.print(daten, HEX);
      Serial.print(".");
    }
//    Serial.write(iBus.read());
//    count++;
  }
  if (count > 5) {
    count = 0;
    Serial.println(".");
  }
}

void oldloop() {
  digitalWrite(ledPin, light);
  Serial.print("LED on ");
  delay(50);
  digitalWrite(ledPin, dark);
  delay(100);
  digitalWrite(ledPin, light);
  delay(50);
  digitalWrite(ledPin, dark);
  Serial.print("LED off ");
  count++;
  if(count > 6) {
    count = 0;
    Serial.println(ledPin);
  }
  delay(2000);
}
