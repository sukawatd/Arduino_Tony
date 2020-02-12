/*
  AnalogOutput

  Activate DAC on pin AIO10. Output 2.5 volt.

  All AIO pins support ADC/DAC 12-bit precision ; range 0-10 volt.
  
  Compatible board: Tony SX E32 pro
*/

int pinout = AIO10;   // Analog pin of 'SLOT6'

void setup() {
  Serial.begin(115200);
  // Convert expected voltage to digital value
  int value = 2.5 * (4095.0 / 10.0);  // Output 2.5 volt
  dacWrite(pinout, value);
}

void loop() {
  
}
