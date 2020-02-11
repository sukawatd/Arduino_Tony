#include "Tony.h"
#include "pins_arduino.h"
#include "Wire.h"

#define DS3231_ADDR_    0x68

#ifndef SLOT_POWER
#define SLOT_POWER 2
#endif

TonyClass TONY;
tonyGPIO _tonyio;


const tony_slot_t SLOT_SELECT[12] = {
	{25, 47, &Serial1},	// SLOT1
	{26, 46, &Serial1},	// SLOT1_U
	{27, 49, &Serial1},	// SLOT2
	{14, 48, &Serial1},	// SLOT2_U
	{57, 51, &Serial1},	// SLOT3
	{56, 50, &Serial1},	// SLOT3_U
	{52, 41, &Serial2},	// SLOT4
	{53, 40, &Serial2},	// SLOT4_U
	{54, 42, &Serial2},	// SLOT5
	{55, 43, &Serial2},	// SLOT5_U
	{ 4, 44, &Serial2},	// SLOT6
	{13, 45, &Serial2}	// SLOT6_U
};

void TonyClass::begin() {
	Wire.begin();
	extraPinOn();
	slotPowerOn();
	
	// check RTC
	Wire.beginTransmission(DS3231_ADDR_);
	uint8_t error = Wire.endTransmission();
	if(error) {
		_activeDevice |= 0x01;
	}
	else {
		_activeDevice &= ~0x01;
	}
}

void TonyClass::slotPowerOn() {
	pinMode(SLOT_POWER, OUTPUT);
	digitalWrite(SLOT_POWER, HIGH);
	delay(100);
}

void TonyClass::slotPowerOff() {
	pinMode(SLOT_POWER, OUTPUT);
	digitalWrite(SLOT_POWER, LOW);
}

void TonyClass::extraPinOn() {
	bool chip_ok = _tonyio.activateChipIO();
	if(chip_ok) {
		_activeDevice |= 0x02;
	}
	else {
		_activeDevice &= ~0x02;
	}
	
	bool config_ok = _tonyio.defaultConfig();
	if(config_ok) {
		_activeDevice |= 0x04;
	}
	else {
		_activeDevice &= ~0x04;
	}
}

void TonyClass::extraPinOff() {
	_tonyio.deactivateChipIO();
	_activeDevice &= ~0x06;
}

bool TonyClass::isrtc_rdy() {
	return _activeDevice & 0x01;
}

bool TonyClass::isxpin_rdy() {
	return _activeDevice & 0x04;
}




