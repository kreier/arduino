// Setup with 10 keys as defined in the root folder and used with kreier/remote and BitBlue on iOS

#include <NewPing.h>
#include <Servo.h>

#define PIN_BUZZER     4
#define PIN_TRIGGER    7
#define PIN_ECHO       8
#define PIN_SERVO      9
#define PIN_E1        10 // enable - with PWM
#define PIN_M1        12
#define PIN_E2        11
#define PIN_M2        13
#define MAX_DISTANCE 350
#define FWD            F // easier to change back for inflexible software - forward
#define BWD            B // backward
#define LEFT           L
#define RIGHT          R
#define SELECT         M
#define START          S
#define TRIANGLE       T // B on BitBlue
#define CIRCLE         C // Y
#define STOP           X // X
#define SQUARE         Q // A


int  spd = 0;
char BTinput = '0';
int  DistanceCm;
int  pos = 0;
int  mode = 1;

NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);
Servo myservo;  

void distance() {
   DistanceCm = sonar.ping_cm(); // 10 pings per second  
}

void buz() {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(50);
    digitalWrite(PIN_BUZZER, LOW);
}

void beep(int beeps) {
  for(int i = 0; i < beeps; i++) {
    buz();
    delay(50);
  }
}

void setup() {
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  analogWrite(PIN_E1, spd);
  analogWrite(PIN_E2, spd);
  myservo.attach(PIN_SERVO);
  myservo.write(90);

  beep(2);
  Serial1.begin(9600);  // HC-10 on pin 0 and 1 
}
 
void loop() {
  if (Serial1.available()) 
  {
    BTinput = Serial1.read();
    // MODE 1: Drive
    if(BTinput == 'F'  && mode == 1) { // up - forward
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_M2, HIGH);
        Serial1.write("forward");
        if(spd == 0) spd = 200;
    }
    if(BTinput == 'B' && mode == 1) { // down - backward
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_M2, LOW);
        Serial1.write("backward");
        if(spd == 0) spd = 200;
    }
    if(BTinput == 'LEFT' && mode == 1) { // left turn
        digitalWrite(PIN_M1, HIGH);
        digitalWrite(PIN_M2, LOW);
        Serial1.write("left");
        if(spd == 0) spd = 128;
    }
    if(BTinput == 'RIGHT' && mode == 1) { // right turn
        digitalWrite(PIN_M1, LOW);
        digitalWrite(PIN_M2, HIGH);
        Serial1.write("right");
        if(spd == 0) spd = 128;
    }
    if(BTinput == 'H') {          // square  - A - autonomus with the servo
      for (pos = 30; pos <= 150; pos += 1) { 
        myservo.write(pos);   
        delay(15);      
      }
      for (pos = 150; pos >= 30; pos -= 1) { 
         myservo.write(pos);              
         delay(15);    
      }
      myservo.write(90);
    }
    if(BTinput == 'E') spd = 255; // triangle - B - FAST
    if(BTinput == 'F') {          // circle   - Y - SELECT
      // what is my mode? Beep 1 for remote 2 for autonomus and 3 for autonomus with ultrasonic beep
      digitalWrite(PIN_BUZZER, HIGH);  
      delay(50);
      digitalWrite(PIN_BUZZER, LOW);
      delay(50);
      digitalWrite(PIN_BUZZER, HIGH);
      delay(50); 
    }
    if(BTinput == 'STOP') spd = 0;   // cross   - X - STOP
    analogWrite(PIN_E1, spd);
    analogWrite(PIN_E2, spd);
    digitalWrite(PIN_BUZZER, HIGH);    
    delay(5);
    digitalWrite(PIN_BUZZER, LOW);
  }
    distance();
}
