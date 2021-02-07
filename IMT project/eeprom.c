
#include "eeprom.h"

void EEPROM_voidInit(void)
{
	i2c_init_master();
}



void EEPROM_voidSendDataByte(u16 address, u8 data)
{
    i2c_start();
	i2c_send_slave_address_with_write_req( 0b01010000 | A2<<2 | ((address & 0x0300)>>8)  );
	i2c_write_byte((u8)address);
	i2c_write_byte(data);
	i2c_stop();
	_delay_ms(10);
    return;
}



u8 EEPROM_u8ReadDataByte(u16 address)
{
	u8 data;
	i2c_start();
	i2c_send_slave_address_with_write_req( 0b01010000 | A2<<2 | ((address & 0x0300)>>8)  );
    i2c_write_byte((u8)address);
	i2c_repeated_start();
	i2c_send_slave_address_with_read_req( 0b01010000 | A2<<2 | ((address & 0x0300)>>8)  );
	data = i2c_read_byte();
	i2c_stop();
	_delay_ms(10);
    return data;
}
