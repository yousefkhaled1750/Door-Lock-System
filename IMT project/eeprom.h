

#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_voidInit(void);
void EEPROM_voidSendDataByte(unsigned short address, unsigned char data);
unsigned char EEPROM_u8ReadDataByte(unsigned short address);
 
#endif








