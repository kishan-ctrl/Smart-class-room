// C++ code
//
int gasSensor = 0;

int temperature = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  gasSensor = analogRead(A0);
  temperature = map(((analogRead(A1) - 20) * 3.04), 0, 1023, -20, 120);
  delay(1000); // Wait for 1000 millisecond(s)
  Serial.println(temperature);
  Serial.println(gasSensor);
  if (gasSensor >= 400) {
    tone(7, 5274, 100); // play tone 100 (E8 = 5274 Hz)
  } else {
    digitalWrite(7, LOW);
  }
  if (temperature <= 30) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
}
