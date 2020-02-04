#ifndef TONY_EXTENDED_GPIO_H
#define TONY_EXTENDED_GPIO_H

#include "esp32-hal.h"
#include "tony-max11301.h"

#define digitalPinIsValidEx(pin)      ((pin) < 60)
#define digitalPinIsTonyExtend(pin)   ((pin) < 60 && (pin) >= 40)

#define TONY_POWER_MAX11301   12

class tonyGPIO {
	public:
		void activeMax();
		void inactiveMax();
		bool defaultConfig();
		
		void pinmode(uint8_t pin, uint8_t mode);
		void digitalwrite(uint8_t pin, uint8_t val);
		int digitalread(uint8_t pin);
		void dacwrite(uint8_t pin, uint16_t val);
		uint16_t analogread(uint8_t pin);
		uint16_t dacmonitor(uint8_t pin, uint16_t val); 	// write+read in the same pin
		
	private:
		
};

#endif
