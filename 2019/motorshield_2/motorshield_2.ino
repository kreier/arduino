int E1 = 10; // enable pin (PWM) for motor 1
int M1 = 12;
int E2 = 11; // PWM for motor 2
int M2 = 13;

int i;

void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Start motor in 5 seconds.");
  for(i = 0 ; i <=30 ; i++)
  {
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
  }
}

void loop()
{
  { 
    for(i = 0 ; i <= 255; i+=5)
    {
      digitalWrite(M1,HIGH);
      digitalWrite(M2,HIGH);
      analogWrite(E1, i);
      analogWrite(E2, i);
      delay(100);
    }
    delay(2000);
  }
  { 
    for(i = 0 ; i <= 255; i+=5)
    {
      digitalWrite(M1,LOW);
      digitalWrite(M2,LOW);
      analogWrite(E1, i);
      analogWrite(E2, i);
      delay(100);
    }
    delay(2000);
  }
} 
