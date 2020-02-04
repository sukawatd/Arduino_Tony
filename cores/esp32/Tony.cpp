#include "Tony.h"

#define TONY_MAX11301_ADDR  0x38
#define TONY_DS3231_ADDR    0x68

TonyClass TONY;
tonyGPIO _tonyio;

const DRAM_ATTR tony_slot_t tony_slot[12] = {
	{25, 47, Serial1},	// SLOT1
	{26, 46, Serial1},	// SLOT1_U
	{27, 49, Serial1},	// SLOT2
	{14, 48, Serial1},	// SLOT2_U
	{57, 51, Serial1},	// SLOT3
	{56, 50, Serial1},	// SLOT3_U
	{52, 41, Serial2},	// SLOT4
	{53, 40, Serial2},	// SLOT4_U
	{54, 42, Serial2},	// SLOT5
	{55, 43, Serial2},	// SLOT5_U
	{ 4, 44, Serial2},	// SLOT6
	{13, 45, Serial2}	// SLOT6_U
};

void TonyClass::begin() {
	activePower();
	activePinExtra();
}

void TonyClass::activePower() {
	pinMode(TONY_POWER_PIN, OUTPUT);
	digitalWrite(TONY_POWER_PIN, HIGH);
	delay(100);
}

void TonyClass::inactivePower() {
	pinMode(TONY_POWER_PIN, OUTPUT);
	digitalWrite(TONY_POWER_PIN, LOW);
}

void TonyClass::activePinExtra() {
	_tonyio.activeMax();
	delay(100);
	check_onboard();
	bool max_ok = _tonyio.defaultConfig();
	if(max_ok) {
		_activeDevice |= 0x04;
	}
	else {
		_activeDevice &= ~0x04;
	}
}

void TonyClass::inactivePinExtra() {
	_tonyio.inactiveMax();
	delay(100);
	check_onboard();
}

void TonyClass::check_onboard() {
	Wire.begin();
	uint8_t error;
	
	Wire.beginTransmission(TONY_DS3231_ADDR);
	error = Wire.endTransmission();
	if(!error) {
		_activeDevice |= 0x01;
	}
	else {
		_activeDevice &= ~0x01;
	}
	delay(10);
	
	Wire.beginTransmission(TONY_MAX11301_ADDR);
	error = Wire.endTransmission();
	if(!error) {
		_activeDevice |= 0x02;
	}
	else {
		_activeDevice &= ~0x02;
	}
}

bool TonyClass::isrtc_rdy() {
	return _activeDevice & 0x01;
}

bool TonyClass::ismax_rdy() {
	return _activeDevice & 0x04;
}




