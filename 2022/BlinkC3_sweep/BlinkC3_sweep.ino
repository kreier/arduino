/* Blink AI-C3*/
// I don't know which pin is for this pixel. Let's try out

int ledPin = 0;
bool light = HIGH;    // LORA915, T-Koala, T8, Arduino
bool dark  = !light;
int count = 0; 

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("lost");
  delay(2000);
  Serial.println("Let's start!");
  delay(2000);
}

void loop() {
  Serial.println(" ");
  Serial.print("Tested PIN for LED: ");
  Serial.print(ledPin);
  delay(2000);
  digitalWrite(ledPin, light);
  Serial.print("  LED on ");
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
  ledPin++;
}
