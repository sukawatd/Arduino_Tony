#include "tony-hal-gpio.h"

MAX11301 _max11301;

void tonyGPIO::activeMax() {
	pinMode(TONY_POWER_MAX11301, OUTPUT);
	digitalWrite(TONY_POWER_MAX11301, HIGH);
}

void tonyGPIO::inactiveMax() {
	pinMode(TONY_POWER_MAX11301, OUTPUT);
	digitalWrite(TONY_POWER_MAX11301, LOW);
}

bool tonyGPIO::defaultConfig() {
	return _max11301.Config_deviceControl();
}

void tonyGPIO::pinmode(uint8_t pin, uint8_t mode) {
	if(!digitalPinIsValidEx(pin)) {
		return;
	}
	
	if(digitalPinIsTonyExtend(pin)) {
		pin = pin - 40;
		if(mode == INPUT) {
			_max11301.Basic_Config_Port_For_GPI(pin, 3276); 	// Threshold 3276 = 2.0V, 0xFFF = 2.5V(MAX)
		}
		else if(mode == OUTPUT) {
			_max11301.Basic_Config_Port_For_GPO(pin, 1352); 	// Logic's output 1352 = 3.3V
		}
	}
	else 
		pinMode(pin, mode);
}

void tonyGPIO::digitalwrite(uint8_t pin, uint8_t val) {
	if(!digitalPinIsValidEx(pin)) {
		return;
	}
	
	if(digitalPinIsTonyExtend(pin)) {
		pin = pin - 40;
		if(val) {
			_max11301.writeGPO(pin, 1352);		// Logic's output 1352 = 3.3V
		}
		else {
			_max11301.writeGPO(pin, 0);
		}
	}
	else 
		digitalWrite(pin, val);
}

int tonyGPIO::digitalread(uint8_t pin) {
	if(!digitalPinIsValidEx(pin)) {
		return 0;
	}
	
	if(digitalPinIsTonyExtend(pin)) {
		pin = pin - 40;
		return _max11301.readGPI(pin);
	}
	else 
		digitalRead(pin);
}

void tonyGPIO::dacwrite(uint8_t pin, uint16_t val) {
	if(digitalPinIsTonyExtend(pin)) {
		pin = pin - 40;
		_max11301.Basic_Config_Port(pin, DACtype);
		_max11301.writeDAC(pin, val);					// Output: 0-10V, precision 12 bits
	}
	else 
		dacWrite(pin, val);
}

uint16_t tonyGPIO::analogread(uint8_t pin) {
	uint16_t dataADC = 0;
	if(digitalPinIsTonyExtend(pin)) {
		pin = pin - 40;
		_max11301.Basic_Config_Port(pin, ADCtype1);
		dataADC = _max11301.readADC(pin);				// Read ADC range 0-10V
	}
	else {
		dataADC = analogRead(pin);						// Read ADC range 0-3.3V
	}
	return dataADC;
}

uint16_t tonyGPIO::dacmonitor(uint8_t pin, uint16_t val) {
	uint16_t dataADC = 0;
	if(digitalPinIsTonyExtend(pin)) {
		pin = pin - 40;
		_max11301.Basic_Config_Port_For_DACADC(pin, val);
		delay(100);
		dataADC = _max11301.readADC(pin);
	}
	return dataADC;
}




