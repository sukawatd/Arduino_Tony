#ifndef TONY_H
#define TONY_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "tony-max11301.h"
#include "tony-hal-gpio.h"

typedef struct {
	uint8_t ioa;			// GPIO pin of SLOTn (pin A)
	uint8_t iob;			// GPIO pin of SLOTn (pin B)
	HardwareSerial *ser; 	// SERIAL of SLOTn
} tony_slot_t;

class TonyClass {
	public:
		TonyClass() {}
		~TonyClass() {}
		void begin();
		void slotPowerOn();
		void slotPowerOff();
		void extraPinOn();
		void extraPinOff();
		bool isrtc_rdy();
		bool isxpin_rdy();
		
	private:
		uint8_t _activeDevice = 0x00;   // >>   -----------------------------------------------------
		                                // bit |  7  |  6  |  5  |  4  |  3  |   2   |   1   |   0   |
		                                //      -----------------------------------------------------
		                                //     |           reserved          | x-pin |chip IO|  RTC  |
		                                //     |                             |  rdy  |  rdy  |  rdy  |
		                                //      -----------------------------------------------------
};

extern TonyClass TONY;
extern tonyGPIO _tonyio;
extern const tony_slot_t SLOT_SELECT[12];

#endif
