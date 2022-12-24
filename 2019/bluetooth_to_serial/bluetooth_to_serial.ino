void setup() {
  Serial1.begin(9600);  // serial port Arduino Leonardo pin 0 and 1
  Serial.begin(9600);   // usb to computer - wait 10 seconds!
}
 
void loop() {
  if (Serial1.available()) Serial.write(Serial1.read());
  if (Serial.available()) Serial1.write(Serial.read()); // Select NL & CR
}
