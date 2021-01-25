
#include "eeprom.h"
#include "I2C.h"
#include <util/delay.h>

void EEPROM_voidInit(void)
{
	i2c_init_master();
}



void EEPROM_voidSendDataByte(unsigned short address, unsigned char data)
{
    i2c_start();
	i2c_send_slave_address_with_write_req( 0b01010000 /*| ((address & 0x0700)>>8) */);
	i2c_write_byte((unsigned char)address);
	i2c_write_byte(data);
	i2c_stop();
	_delay_ms(100);
    return;
}



unsigned char EEPROM_u8ReadDataByte(unsigned short address)
{
	unsigned char data;
	i2c_start();
	i2c_send_slave_address_with_write_req( 0b01010000 /*| ((address & 0x07)>>8) */);
    i2c_write_byte((unsigned char)address);
	i2c_repeated_start();
	i2c_send_slave_address_with_read_req( 0b01010000 /*| ((address & 0x07)>>8)*/ );
	data = i2c_read_byte();
	i2c_stop();
	_delay_ms(100);
    return data;
}
