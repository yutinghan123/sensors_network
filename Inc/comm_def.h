#ifndef __COMM_DEF_H
#define __COMM_DEF_H
typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL_t;
uint16_t crc16_calc(uint8_t * pchMsg, uint16_t wDataLen);
#endif
