#include <AFMotor.h> // download from subdirectory 'library' here and install zip file
#include <SoftwareSerial.h>

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
    if (BTinput == 'A')// up
    {
      motor1.run(FORWARD);
      motor4.run(FORWARD);
    }
    if (BTinput == 'C')// down
    {
      motor1.run(BACKWARD);
      motor4.run(BACKWARD);
    }
    if (BTinput == 'D')// left
    {
      motor1.run(FORWARD);
      motor4.run(BACKWARD);
    }
    if (BTinput == 'B')// right
    {
      motor1.run(BACKWARD);
      motor4.run(FORWARD);
    }      
    if (BTinput == 'G')  // that's the "X" key
    {
      motor1.run(RELEASE);      // stopped
      motor4.run(RELEASE);
    }
    if (BTinput == 'E')// faster - plus 10 - triangle
    {
      speed = speed + 10;
    }
    if (BTinput == 'H')// slower - minus 10 - square
    {
      speed = speed - 10;
    } 
    if (BTinput == 'F')// maximum speed - circle
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
