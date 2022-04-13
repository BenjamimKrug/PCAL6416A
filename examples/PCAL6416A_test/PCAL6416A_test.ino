/*

  PCAL6416A_test.ino - example using PCAL6416A library

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
#include <PCAL6416A.h>

// instantiate PCAL6416A object
PCAL6416A device(Wire);//address at 0x21

void setup() {
  // initialize i2c interface
  Wire.begin(16, 4);
  // initialize serial interface
  Serial.begin(115200);
  device.pinMode(P00 & P01 & P02 & P03, OUTPUT);
  device.pinMode(P04 & P05 & P06 & P07, OUTPUT);
  device.pinMode(P13 & P14 & P15, INPUT);
  Serial.println(device.getConfig(), BIN);
}

void loop() {
  uint8_t status;

  Serial.print("Address ");
  Serial.print(device.getAddress(), HEX);
  Serial.print(", ");

  // attempt to write on port 1-3
  status = device.digitalWrite(P00 & P01 & P03, LOW);
  if (status == TWI_SUCCESS)
    Serial.println("success");
  else {
    Serial.print("write error ");
    Serial.println(status, DEC);
  }

  status = device.digitalWrite(P04 & P05 & P07, HIGH);
  if (status == TWI_SUCCESS)
    Serial.println("success");
  else {
    Serial.print("write error ");
    Serial.println(status, DEC);
  }

  // attempt to read
  Serial.printf("P00: %i,", device.digitalRead(P00, status));
  Serial.printf("P01: %i,", device.digitalRead(P01, status));
  Serial.printf("P02: %i,", device.digitalRead(P02, status));
  Serial.printf("P03: %i,", device.digitalRead(P03, status));
  Serial.printf("P04: %i,", device.digitalRead(P04, status));
  Serial.printf("P05: %i,", device.digitalRead(P05, status));
  Serial.printf("P06: %i,", device.digitalRead(P06, status));
  Serial.printf("P07: %i,", device.digitalRead(P07, status));
  Serial.printf("P10: %i,", device.digitalRead(P10, status));
  Serial.printf("P11: %i,", device.digitalRead(P11, status));
  Serial.printf("P12: %i,", device.digitalRead(P12, status));
  Serial.printf("P13: %i,", device.digitalRead(P13, status));
  Serial.printf("P14: %i,", device.digitalRead(P14, status));
  Serial.printf("P15: %i,", device.digitalRead(P15, status));
  Serial.printf("P16: %i,", device.digitalRead(P16, status));
  Serial.printf("P17: %i\n", device.digitalRead(P17, status));
  Serial.print("ports: ");
  Serial.println(device.getPorts(), BIN);
  if (status == TWI_SUCCESS)
    Serial.println("success reading");
  else {
    Serial.print("read error ");
    Serial.println(status, DEC);
  }

  delay(1000);
}