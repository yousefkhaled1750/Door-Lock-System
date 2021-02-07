

#ifndef EEPROM_H_
#define EEPROM_H_
#include "I2C.h"
#include "LIB/STD_TYPES.h"
#include <util/delay.h>

#define A2 0

void EEPROM_voidInit(void);
void EEPROM_voidSendDataByte(u16 address, u8 data);
u8 EEPROM_u8ReadDataByte(u16 address);
 
#endif








