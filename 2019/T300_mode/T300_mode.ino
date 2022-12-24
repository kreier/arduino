#define PIN_BUZZER     4

char BTinput = '0';

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
  pinMode(PIN_BUZZER, OUTPUT);
  beep(2);
  Serial1.begin(9600);  // HC-10 on pin 0 and 1 
  Serial.begin(57600);
}

void loop() {
  if (Serial1.available()) 
  {
    BTinput = Serial1.read();
    if(BTinput == 'F') Serial.write("forward");
    if(BTinput == 'B') Serial.write("backward");
  }
}
