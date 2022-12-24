// This is for the BitBlue app from Bitbus inc.
// Standard settings: A B X Y F B R L S-start C-Select
#include <SoftwareSerial.h> 

int E1 = 10; // enable - with PWM
int M1 = 12;
int E2 = 11;
int M2 = 13;
int spd = 0;
char BTinput = '0';

SoftwareSerial BTSerial(8, 3);   // RX | TX

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  analogWrite(E1, spd);
  analogWrite(E2, spd);
  
  BTSerial.begin(9600);  // HC-05 default speed in AT 38400
}
 
void loop() {
  if (BTSerial.available()) 
  {
    BTinput = BTSerial.read();
    if(BTinput == 'F') { // up - forward
        digitalWrite(M1, HIGH);
        digitalWrite(M2, HIGH);
        if(spd == 0) spd = 200;
    }
    if(BTinput == 'B') { // down - backward
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        if(spd == 0) spd = 200;
    }
    if(BTinput == 'L') { // left turn
        digitalWrite(M1, HIGH);
        digitalWrite(M2, LOW);
        if(spd == 0) spd = 128;
    }
    if(BTinput == 'R') { // right turn
        digitalWrite(M1, LOW);
        digitalWrite(M2, HIGH);
        if(spd == 0) spd = 128;
    }
    if(BTinput == 'A') spd = 75;  // slow
    if(BTinput == 'B') spd = 100; // medium
    if(BTinput == 'Y') spd = 255; // turbo
    if(BTinput == 'X') spd = 0;   // stop
    analogWrite(E1, spd);
    analogWrite(E2, spd);
  }
}
