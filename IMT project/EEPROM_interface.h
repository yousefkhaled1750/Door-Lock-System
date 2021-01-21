/*****************************************************************/
/*****************************************************************/
/********************		Author: Amgad Samir		**************/
/********************		Layer: HAL				**************/
/********************		SWC: EEPROM				**************/
/********************		Version: 1.00			**************/
/********************		Date: 13-10-2020		**************/
/*****************************************************************/
/*****************************************************************/

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
#include "LIB/STD_TYPES.h"
#include "LIB/Bit_math.h"
#include "TWI_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

#endif
