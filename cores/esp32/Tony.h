#ifndef TONY_H
#define TONY_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "tony-max11301.h"
#include "tony-hal-gpio.h"

#define  TONY_POWER_PIN        2

typedef struct {
	uint8_t io;				// IO pin of SLOTn
	uint8_t aio;			// AIO pin of SLOTn
	HardwareSerial uart;	// SERIAL of SLOTn
} tony_slot_t;

class TonyClass {
	public:
		TonyClass() {}
		~TonyClass() {}
		void begin();
		void activePower();
		void inactivePower();
		void activePinExtra();
		void inactivePinExtra();
		void check_onboard();
		bool isrtc_rdy();
		bool ismax_rdy();
		
	private:
		uint8_t _activeDevice = 0x00;
};

extern TonyClass TONY;
extern tonyGPIO _tonyio;
extern const tony_slot_t tony_slot[12];

#endif
