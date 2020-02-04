#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#ifdef __cplusplus

#include "Tony.h"

#define pinMode(p, m)      ((p)<40)? pinMode(p, m)     : _tonyio.pinmode(p, m)
#define digitalWrite(p, v) ((p)<40)? digitalWrite(p, v): _tonyio.digitalwrite(p, v)
#define digitalRead(p)     ((p)<40)? digitalRead(p)    : _tonyio.digitalread(p)
#define dacWrite(p, v)     ((p)<40)? dacWrite(p, v)    : _tonyio.dacwrite(p, v)
#define analogRead(p)      ((p)<40)? analogRead(p)     : _tonyio.analogread(p)
#define dacMonitor(p, v)   _tonyio.dacmonitor(p, v)

#endif /* __cplusplus */

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t TX = 1;			// esp pin
static const uint8_t RX = 3;			// esp pin

static const uint8_t SDA = 21;			// esp pin
static const uint8_t SCL = 22;			// esp pin

static const uint8_t SS    = 5;			// esp pin
static const uint8_t MOSI  = 23;		// esp pin
static const uint8_t MISO  = 19;		// esp pin
static const uint8_t SCK   = 18;		// esp pin

static const uint8_t DAC1 = 25;			// esp pin
static const uint8_t DAC2 = 26;			// esp pin

// Mapping of analog pins (AIO)
static const uint8_t AIO0  = 47;
static const uint8_t AIO1  = 46;
static const uint8_t AIO2  = 49;
static const uint8_t AIO3  = 48;
static const uint8_t AIO4  = 51;
static const uint8_t AIO5  = 50;
static const uint8_t AIO6  = 41;
static const uint8_t AIO7  = 40;
static const uint8_t AIO8  = 42;
static const uint8_t AIO9  = 43;
static const uint8_t AIO10 = 44;
static const uint8_t AIO11 = 45;

// Mapping of digital pins (IO)
static const uint8_t IO0   = 25;		// esp pin
static const uint8_t IO1   = 26;		// esp pin
static const uint8_t IO2   = 27;		// esp pin
static const uint8_t IO3   = 14;		// esp pin
static const uint8_t IO4   = 57;
static const uint8_t IO5   = 56;
static const uint8_t IO6   = 52;
static const uint8_t IO7   = 53;
static const uint8_t IO8   = 54;
static const uint8_t IO9   = 55;
static const uint8_t IO10  = 4; 		// esp pin
static const uint8_t IO11  = 13;		// esp pin

static const uint8_t IO12  = 15; 		// esp pin (LED_BUILTIN)
static const uint8_t IO13  = 2;			// esp pin (Peripheral's Power)
static const uint8_t IO14  = 12; 		// esp pin (MAX11301's Power)
static const uint8_t IO15  = 58; 		// Relay 1
static const uint8_t IO16  = 59; 		// Relay 2

#define  LED_BUILTIN    15

#define  SLOT1          0
#define  SLOT1_U        1
#define  SLOT2          2
#define  SLOT2_U        3
#define  SLOT3          4
#define  SLOT3_U        5
#define  SLOT4          6
#define  SLOT4_U        7
#define  SLOT5          8
#define  SLOT5_U        9
#define  SLOT6          10
#define  SLOT6_U        11

#endif /* Pins_Arduino_h */
