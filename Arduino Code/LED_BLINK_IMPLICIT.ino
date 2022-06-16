const int vibPin = 2;
void setup() {
  //Short vibration
  pinMode (vibPin, OUTPUT);
  delay(500);
  digitalWrite (vibPin, HIGH);
  delay(500);
  digitalWrite (vibPin, LOW);
  
  //Long Vibration
  delay(1500);
  digitalWrite (vibPin, HIGH);
  delay(1500);
  digitalWrite (vibPin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  //  delay(200);
  //  digitalWrite (vibPin, HIGH);
  //  delay(200);
  //  digitalWrite (vibPin, LOW);
}
