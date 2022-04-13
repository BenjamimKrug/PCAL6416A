/*
  PCAL6416A.cpp - Arduino library for TI PCAL6416A 16-bit I2C
  I/O expander.

  Library:: PCAL6416A
  Author:: BenKrug <benjamimkrug@gmail.com>

  Copyright:: 2009-2016 BenKrug

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef PCAL6416A_H
#define PCAL6416A_H

// include types & constants of Wiring core API
#include <Arduino.h>

// include twi/i2c library
#include <Wire.h>

#define TWI_SUCCESS 0// I2C/TWI success (transaction was successful)
#define TWI_DEVICE_NACK 2// I2C/TWI device not present (address sent, NACK received)
#define TWI_DATA_NACK 3// I2C/TWI data not received (data sent, NACK received)
#define TWI_ERROR 4// I2C/TWI other error

#define P00 0b1111111111111110
#define P01 0b1111111111111101
#define P02 0b1111111111111011
#define P03 0b1111111111110111
#define P04 0b1111111111101111
#define P05 0b1111111111011111
#define P06 0b1111111110111111
#define P07 0b1111111101111111
#define P10 0b1111111011111111
#define P11 0b1111110111111111
#define P12 0b1111101111111111
#define P13 0b1111011111111111
#define P14 0b1110111111111111
#define P15 0b1101111111111111
#define P16 0b1011111111111111
#define P17 0b0111111111111111

// CLASS DEFINITIONS
class PCAL6416A
{
  public:
    // public member functions
    PCAL6416A(TwoWire &w,uint8_t);
    PCAL6416A(TwoWire &w);
	uint8_t  pinMode(uint16_t port, uint8_t state);
    bool  digitalRead(uint16_t port, uint8_t &status);
    uint8_t  digitalWrite(uint16_t port, bool state);
    uint8_t  getAddress();
    uint16_t getPorts();
	uint16_t getConfig();

  private:
	TwoWire *wire;
	// Storage object for PCAL6416A ports 1 (P17..P10), 0 (P07..P00).
	uint16_t ports_, ports_config;
	// Factory pre-set slave address.
    uint8_t BASE_ADDRESS = 0x21;
	
};
#endif // PCAL6416A_H
