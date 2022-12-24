#include <Wire.h> 

#define DIRA 0
#define PWMA 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting...");

  Serial.println("Preparing motor...");
  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  analogWrite(PWMA,0);
  digitalWrite(DIRA,1);
  delay(5000);
  Serial.println("Starting motor...");
  analogWrite(PWMA,5);
  delay(5000);
  Serial.println("Speed: 50");
  analogWrite(PWMA,50);
  delay(5000);
  Serial.println("Speed: 100");
  analogWrite(PWMA,100);
  delay(5000);
  Serial.println("Speed: 300");
  analogWrite(PWMA,300);
  delay(5000);
  Serial.println("Speed: 1000");
  analogWrite(PWMA,1000);
  delay(3000);
  Serial.println("Speed: 0");
  analogWrite(PWMA,0);
  delay(3000);
  digitalWrite(DIRA,0);
  Serial.println("Speed: -250");  
  analogWrite(PWMA,250);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
