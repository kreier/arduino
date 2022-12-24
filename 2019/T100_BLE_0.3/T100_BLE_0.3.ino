#include <AFMotor.h> // download from subdirectory 'library' here and install zip file
#include <SoftwareSerial.h>  // updated to match T300 with key assignment

#define LED_PIN 13
 
AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor4(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
SoftwareSerial BTSerial(A0, 3);   // RX | TX  -  pin 2 creates errors on my motor shield, analog pin is fine ...
char BTinput = '0';
byte speed = 200;

void setup() {
  motor1.setSpeed(100);
  motor4.setSpeed(100);     // set the speed to 200/255
  BTSerial.begin(9600);  // HC-10 default speed
  Serial.begin(57600);   // just to check while programming
}
 
void loop() {
  if (BTSerial.available()) 
  {
    BTinput = BTSerial.read();
    if (BTinput == 'F')      // forward  - A
    {
      motor1.run(FORWARD);
      motor4.run(FORWARD);
    }
    if (BTinput == 'B')      // backward - C
    {
      motor1.run(BACKWARD);
      motor4.run(BACKWARD);
    }
    if (BTinput == 'L')      // left     - D
    {
      motor1.run(FORWARD);
      motor4.run(BACKWARD);
    }
    if (BTinput == 'R')      // right    - B
    {
      motor1.run(BACKWARD);
      motor4.run(FORWARD);
    }      
    if (BTinput == 'X')      // that's the "X" key      - G
    {
      motor1.run(RELEASE);      // stopped
      motor4.run(RELEASE);
    }
    if (BTinput == 'C')  // faster - plus 10  - circle  - F
    {
      speed = speed + 10;
    }
    if (BTinput == 'Q')  // slower - minus 10 - square  - H
    {
      speed = speed - 10;
    } 
    if (BTinput == 'T')  // turbo, fastest - triangle   - E
    {
      speed = 255;
    }
    if( speed > 255 ) speed = 255;
    motor1.setSpeed(speed);
    motor4.setSpeed(speed);
    Serial.print("recieved: ");
    Serial.print( BTinput );
    Serial.print(" speed: ");
    Serial.println( speed );
  }
}
