/*
  AnalogOutputTriangleWave

  Activate DAC on pin AIO11. Create the Triangle Wave 0-10 volt.

  All AIO pins support ADC/DAC 12-bit precision ; range 0-10 volt.
  
  Compatible board: Tony SX E32 pro
*/

int pinout = AIO11;     // Analog pin of 'SLOT6_U'

int counter = 0;        // variable for count up
int deltaPoint = 140;   // counter increment per loop
int value = 0;          // voltage value, Range : 0-4095

void setup() {
  Serial.begin(115200);
  Serial.println("Generate Triangle-Wave (pin AIO11)");
  Serial.println("Use Oscilloscope to measure the signals...");
}

void loop() {
  static unsigned long capture_t = millis();
  static bool reported = false;
  
  // Assign the output value
  dacWrite(pinout, value);

  // Update value
  counter += deltaPoint;
  if(counter < 4095) {
    value = counter;
  }
  else if(counter < (4095 * 2)) {
    value = (4095 * 2) - counter;
  }
  else {
    counter -= (4095 * 2);
    value = counter;
    if(!reported) {
      unsigned long period = (millis() - capture_t);
      Serial.println();
      Serial.print("Period = ");
      Serial.print(period);
      Serial.println(" ms");
      reported = true;
    }
  }
}
