/*
  Copyright (c) 2015 Atmel Corp./Thibaut VIARD. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
 * This is the pinmap for Atmel ATmega328P Xplained Mini.
 *
 * The mEDBG component bridges Serial (D0/D1) to USB CDC and
 * allows device ISP programming through CMSIS-DAP.
 *
 * Please, check "ATmega328P Xplained Mini User Guide" at http://www.atmel.com/tools/mega328p-xmini.aspx?tab=documents
 *
 *
 *                                                         +-------+
 *                                                         | |USB| |
 *                                                         | +---+ |
 *                                                         |  | |  |
 *                                        +----------------+  | |  +----------------+
 *                                        |                   | |                  o|  PC5 ADC5 PCINT13 SCL            J200, Digital I/O High
 *                                        |                   | |                  o|  PC4 ADC4 PCINT12 SDA
 *                                        |                +-------+               o|  AREF
 *                                        |                | mEDBG |               o|  GND
 *                                        |                +-------+           D13 o|  PB5 PCINT5 SCK
 *  J202, Power                    IOREF  |o                  | |              D12 o|  PB4 PCINT4 MISO
 *                                 RESET  |o                  | |              D11 o| ~PB3 OC2A PCINT3 MOSI
 *                                   3V3  |o                  | |              D10 o| ~PB2 OC1B PCINT2 !SS
 *                                    5V  |o                  | |               D9 o| ~PB1 OC1A PCINT1
 *                                   GND  |o                  | |               D8 o|  PB0 CLK0 PCINT0 ICP1
 *                                   GND  |o             +------------+             |
 *                                   VIN  |o             | ATmega328P |         D7 o|  PD7 AIN1 PCINT23                J201, Digital I/O Low
 *                                        |              +------------+         D6 o| ~PD6 AIN0 PCINT22 OC0A
 *  J203, Analog         PCINT8 ADC0 PC0  |o A0                                 D5 o| ~PD5 T1 PCINT21 OC0B
 *                       PCINT9 ADC1 PC1  |o A1                                 D4 o|  PD4 T0 PCINT20 XCK
 *                      PCINT10 ADC2 PC2  |o A2                                 D3 o| ~PD3 INT1 PCINT19 OC2B
 *                      PCINT11 ADC3 PC3  |o A3            J204, ISP            D2 o|  PD2 INT0 PCINT18
 *                  SDA PCINT12 ADC4 PC4  |o A4               ooo               D1 o|  PD1 TXD PCINT17 (also on mEDBG/Virtual Communication Port)
 *                  SCL PCINT13 ADC5 PC5  |o A5               ooo               D0 o|  PD0 RXD PCINT16 (also on mEDBG/Virtual Communication Port)
 *                                        |                                         |
 *                                        |          SW0 (D20)  LED0 (D13)          |
 *                                        +-----------------------------------------+
 *
 *
 *                                                         J204, ISP
 *
 *                              [PC6 RESET PCINT14]    [PB5 PCINT5 SCK]    [PB4 PCINT4 MISO]
 *                              [GND]               [PB3 OC2A PCINT3 MOSI] [5V]
 *
 */

#ifndef __PIN_ARDUINO_H__
#define __PIN_ARDUINO_H__

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            (21u)
#define NUM_ANALOG_INPUTS           (6u)

/* SPI pins
 */
static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

/* Wire pins
 */
static const uint8_t SDA = 18;
static const uint8_t SCL = 19;

/* Analog pins
 */
static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 19;

/* Atmel Xplained mini
 * Push button SW0
 */
static const uint8_t SW0 = 20;

#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + A0 : -1)
#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11)

#define PIN_LED_13                  (13u)
#define PIN_LED                     PIN_LED_13
#define LED_BUILTIN                 PIN_LED_13

#define PIN_BUTTON                  SW0
#define PIN_SW0                     SW0

#define digitalPinToPCICR(p)        (((p) >= 0 && (p) <= 21) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p)     (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)        (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p)     (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
	PD, /* 0 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB, /* 8 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PC, /* 14 */
	PC,
	PC,
	PC,
	PC,
	PC,
	PB  /* Push button SW0 */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(0), /* 14, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(7)  /* 20, Push button SW0 */
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
	NOT_ON_TIMER, /* 0 - port D */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER2B,
	NOT_ON_TIMER,
	TIMER0B,
	TIMER0A,
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* 8 - port B */
	TIMER1A,
	TIMER1B,
	TIMER2A,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* 14 - port C */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER  /* 20, Push button SW0 */
};

#endif // ARDUINO_MAIN

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial

#endif // __PIN_ARDUINO_H__
