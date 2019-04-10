#include "main.h"

const uint16_t wCRCTalbeAbs[] = {
	0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401, \
	0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400\
};
uint16_t crc16_calc(uint8_t * pchMsg, uint16_t wDataLen) 
{
  uint16_t wCRC = 0xFFFF;
  uint16_t i;
  uint8_t chChar;
  for (i = 0; i < wDataLen; i++) {
		chChar = *pchMsg++;
		wCRC = wCRCTalbeAbs[(chChar ^ wCRC) & 15] ^ (wCRC >> 4);
    wCRC = wCRCTalbeAbs[((chChar >> 4) ^ wCRC) & 15] ^ (wCRC >> 4);
  }
  return wCRC;
}
