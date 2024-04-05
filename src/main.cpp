// Global libs
#include <Arduino.h>
// #include <SPI.h>
// #include <SD.h>

// TODO: Stop using Arduino.hString class, use string or char[] (explore string.h, ctype.h)
// 

// Local libs
#include "Base/0_Base.h"

Chemostat* pCH;

void setup() {
  pCH = new Chemostat(); // TODO: [HEAP] Check proper free/delete
  pCH->onsetup();
}

void loop() {

  // DEV
  delay(2000);
  pCH->pMSG->tryReadMsg("$DO:LED-MEASURE!%");
  pCH->onloop();
  pCH->pMSG->tryReadMsg("$STRR:PULSE!:1:500%");
  pCH->onloop();
  delay(200);
  pCH->pMSG->tryReadMsg("$STRR:PULSE!:2:500%");
  pCH->onloop();

  // pCH->onloop();

}

