/*
  DigitalOutputBlink
  
  Turn on the output on IO1 for 1 second, then turn off for 1 second, repeatedly.
  
  Compatible board: Tony platform
*/

int pinout = IO1;   // Digital pin of 'SLOT1_U'

void setup() {
  Serial.begin(115200);
  pinMode(pinout, OUTPUT);
}

void loop() {
  digitalWrite(pinout, HIGH);
  delay(1000);
  digitalWrite(pinout, LOW);
  delay(1000);
}
