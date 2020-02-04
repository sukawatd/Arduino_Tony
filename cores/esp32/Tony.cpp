#include "Tony.h"

#define TONY_MAX11301_ADDR  0x38
#define TONY_DS3231_ADDR    0x68

TonyClass TONY;
tonyGPIO _tonyio;

const DRAM_ATTR tony_slot_t tony_slot[12] = {
	{IO0, AIO0, Serial1},	// SLOT1
	{IO1, AIO1, Serial1},	// SLOT1_U
	{IO2, AIO2, Serial1},	// SLOT2
	{IO3, AIO3, Serial1},	// SLOT2_U
	{IO4, AIO4, Serial1},	// SLOT3
	{IO5, AIO5, Serial1},	// SLOT3_U
	{IO6, AIO6, Serial2},	// SLOT4
	{IO7, AIO7, Serial2},	// SLOT4_U
	{IO8, AIO8, Serial2},	// SLOT5
	{IO9, AIO9, Serial2},	// SLOT5_U
	{IO10, AIO10, Serial2},	// SLOT6
	{IO11, AIO11, Serial2}	// SLOT6_U
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




