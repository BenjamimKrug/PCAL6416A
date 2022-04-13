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

// __________________________________________________________ PROJECT INCLUDES
#include "PCAL6416A.h"

PCAL6416A::PCAL6416A(TwoWire &w,uint8_t address){
  wire = &w;
  BASE_ADDRESS = address;
  ports_ = 0;
}

PCAL6416A::PCAL6416A(TwoWire &w){
  wire = &w;
  BASE_ADDRESS = 0x21;
  ports_ = 0;
}

bool PCAL6416A::digitalRead(uint16_t port, uint8_t &status){
  uint8_t hi, lo;
  
  wire->beginTransmission(BASE_ADDRESS);
  status = wire->endTransmission();

  if (TWI_SUCCESS == status){
    if (wire->requestFrom(BASE_ADDRESS, 2) == 2){
      lo = wire->read();
      hi = wire->read();
      ports_ = word(hi, lo);
	  return ports_ & (~port);
    }
  }
  return 0;
}

uint8_t PCAL6416A::digitalWrite(uint16_t port, bool state){
  uint8_t hi, lo, status;
  uint16_t ports;
  
  wire->beginTransmission(BASE_ADDRESS);
  status = wire->endTransmission();

  if (status == TWI_SUCCESS){
    if (wire->requestFrom(BASE_ADDRESS, 2) == 2){
      lo = wire->read();
      hi = wire->read();
	  ports = word(hi, lo);
	  ports_ = state ? ports | (~port) : ports & port;
	  wire->beginTransmission(BASE_ADDRESS);
	  wire->write(0x02);
      wire->write(lowByte(ports_));
      wire->write(highByte(ports_));
    }
    else
      return TWI_ERROR;	
  }
  return wire->endTransmission();
}

uint8_t PCAL6416A::pinMode(uint16_t port, uint8_t state){
  uint8_t hi, lo, status;
  uint16_t ports;
  wire->beginTransmission(BASE_ADDRESS);
  Wire.write(0x06);
  status = wire->endTransmission();

  if (status == TWI_SUCCESS){
    if (wire->requestFrom(BASE_ADDRESS, 2) == 2){
      lo = wire->read();
      hi = wire->read();
      ports = word(hi, lo);
	  ports_config = state == 2 ? ports & port : ports | ~port;
	  wire->beginTransmission(BASE_ADDRESS);
	  wire->write(0x06);
      wire->write(lowByte(ports_config));
      wire->write(highByte(ports_config));
    }
    else
      return TWI_ERROR;
  }
  return wire->endTransmission();
}

uint8_t PCAL6416A::getAddress(){
  return BASE_ADDRESS;
}

uint16_t PCAL6416A::getPorts(){
  uint8_t hi, lo, status;
  
  wire->beginTransmission(BASE_ADDRESS);
  status = wire->endTransmission();

  if (TWI_SUCCESS == status){
    if (wire->requestFrom(BASE_ADDRESS, 2) == 2){
      lo = wire->read();
      hi = wire->read();
      ports_ = word(hi, lo);
    }
  }
  return ports_;
}

uint16_t PCAL6416A::getConfig(){
  return ports_config;
}
