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

void initCard(void) {
  pinMode(SD_CS, OUTPUT);
  SD.begin(SD_CS, SPI_FULL_SPEED);
}

void initFile(void) {
  char filename[] = "LOG_#000.CSV";
  filename[4] = 'I';
  for (uint16_t i = 0; i < 1000; i++) {
    uint16_t n = i;
    filename[7] = n%10 + '0';
    n /= 10;
    filename[6] = n%10 + '0';
    n /= 10;
    filename[5] = n%10 + '0';
    if (!SD.exists(filename)) {
      _logfile.open(filename, O_CREAT | O_WRITE | O_APPEND);
      break;
    }
  }
}

void initINA219(void) {
  ina219.begin();
  switch (RANGE) {
    case 400:
      ina219.setCalibration_16V_400mA();
      break;
    case 1000:
      ina219.setCalibration_32V_1A();
      break;
    case 2000:
    default:
      break;
  }
}

