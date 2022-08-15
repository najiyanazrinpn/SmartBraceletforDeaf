/*
Set up
A0 - D5
D0 - D4
GND - GND
VCC - 3V3
*/



int led = 2;
int sound_digital = 0;
int sound_analog = 4;

void setup(){
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  pinMode(sound_digital, INPUT);
}

void loop(){
  int val_digital = digitalRead(sound_digital);
  int val_analog = analogRead(sound_analog);

  Serial.print(val_analog);
  Serial.print("\t");
  Serial.println(val_digital);

  if (val_analog > 16)
  {
    digitalWrite (led, HIGH);
//    delay(100);
    }
  else
  {
    digitalWrite (led, LOW);
  }

}
