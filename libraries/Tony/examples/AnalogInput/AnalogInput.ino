/*
  AnalogInput
  
  Read an analog input on pin AIO0(AIO-Zero), converts it to voltage,
  and prints the result to the Serial Monitor.

  All AIO pins support ADC/DAC 12-bit precision ; range 0-10 volt.
  
  Compatible board: Tony SX E32 pro
*/

int pinin = AIO0;   // Analog pin of 'SLOT1'

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(pinin);
  // Convert analog reading from (0-4095) to (0-10V)
  float voltage = sensorValue * (10.0 / 4095.0);
  Serial.println(voltage, 3);
  delay(200);
}
