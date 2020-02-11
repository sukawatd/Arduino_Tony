/*
  SlotSelectFunction

  Demonstrate of creating function with TONY SLOT base.

  Note: SLOT_SELECT[x] have 3 attributes.
        - ioa : The 1st IO pin of the SLOT
        - iob : The 2nd IO pin of the SLOT (Be AIO pin in TonySX E32 pro)
        - ser : Serial port of the SLOT
        
       !> x is a constant value, as follows.
          SLOT1, SLOT2, SLOT3, ... , SLOT11,
          SLOT1_U, SLOT2_U, ... , SLOT11_U
*/

HardwareSerial *ser;  // Store serial pointer of the SLOT...

void digitalWrite_on_slot(uint8_t slot, bool value) {
  uint8_t d_pin = SLOT_SELECT[slot].ioa;  // Get IO pin of the SLOT
  pinMode(d_pin, OUTPUT);                 // Initialize d_pin as an output
  digitalWrite(d_pin, value);             // Turn on d_pin (3.3V)
}

void analogWrite_on_slot(uint8_t slot, int value) {
  uint8_t a_pin = SLOT_SELECT[slot].iob;  // Get AIO pin of the SLOT
  dacWrite(a_pin, value);
}

void serialbegin(uint8_t slot, long baudrate) {
  ser = SLOT_SELECT[slot].ser; // Get serial of the SLOT
  ser->begin(baudrate);
}

void setup() {
  Serial.begin(115200);
  // Turn on digital pin on SLOT1
  digitalWrite_on_slot(SLOT1, HIGH);
  // Analog pin, on SLOT1, output 4.5 volts (1843)
  // Support dacWrite 0-10 volts only on board <TonySX E32 pro>
  analogWrite_on_slot(SLOT1, 1843);
  // Initialize Serial on SLOT1 and print out some text
  serialbegin(SLOT1, 115200);
  delayMicroseconds(100);
  ser->println("SLOT1");
  
  // Print some description on Serial Monitor
  Serial.println("SlotSelectFunction()");
  Serial.println("IO0 is HIGH.");
  Serial.println("AIO0's output is 4.5 volts.");
  Serial.println("Type anything to print on Serial of SLOT1 ...");
}

void loop() {
  if(Serial.available() > 0) {
    ser->write(Serial.read());
  }
}
