/**
Copyright (c) 2016, Clément Ronzon
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of current-data-logger nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SdFat.h>

// Pins:
#define SD_CS               10             // SD chip select pin

// Settings
#define SYNC_INTERVAL       30000          // How often data is stored on SD card (ms)
#define RANGE               400            // The lower the range the higher the resolution, options are: 2000, 1000, 400 (mA)

// Global variables
SdFat SD;SdFile _logfile;
uint32_t _syncTime =        0;
Adafruit_INA219 ina219;
static unsigned long
  _timer =                  0;

void setup(void) {
  initINA219();
  initCard();
  initFile();
  writeHeaders();
  flush2SD();

}

void loop(void) {
  writeData(ina219.getCurrent_mA(), ina219.getBusVoltage_V() + ina219.getShuntVoltage_mV() * 0.001);
  if (millis() - _timer > (unsigned long)SYNC_INTERVAL) {
    flush2SD();
    _timer = millis();
  }
}
