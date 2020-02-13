/* 
  DigitalInput
  
  Read an digital input on pin IO0(IO-Zero), and prints the result to the Serial Monitor.
*/

int pinin = IO0;    // Digital pin of 'SLOT1'

void setup() {
  Serial.begin(115200);
  pinMode(pinin, INPUT);
}

void loop() {
  int state = digitalRead(pinin);
  Serial.println(state);
  delay(200);
}
