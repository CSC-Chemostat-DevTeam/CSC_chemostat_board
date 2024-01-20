#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Hashing
// from: https://forum.arduino.cc/t/simple-checksum-that-a-noob-can-use/300443/3
// TOSYNC
unsigned int crc16_hash(unsigned int crc, char c){
  int i;
  crc ^= c;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1) {
        crc = (crc >> 1) ^ 0xA001;
    } else {
        crc = (crc >> 1);
    }
  }
  return crc;
}

unsigned int crc16_hash(unsigned int crc, String str){
    for (unsigned int i = 0; i < str.length(); i++) {
        crc = crc16_hash(crc, str.charAt(i));
    }
    return crc;
}
