// Global libs
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Local libs
#include "Base/0_Base.h"

Chemostat* pCH;

void setup() {
  pCH = new Chemostat(); // TODO: [HEAP] Check proper free/delete
  pCH->onsetup();
}

void loop() {
  pCH->onloop();
}

