/*
 * IMT project.c
 *
 * Created: 8/18/2020 4:18:16 PM
 * Author : EGYPT_LAPTOP
 */ 

#include "program.h"
#include "MCAL/UART.h"
#include <util/delay.h>



int main (void)
{
	u8 choose;
	extern address;
	UART_voidInit();
	DIO_voidSetPortDirection(DIO_PORTC, DIO_OUTPUT);
	EEPROM_voidInit();
	
	//check for previous data
	if(EEPROM_u8ReadDataByte(0) == 0){	//if there's a user stored in eeprom then get the number of users from the last address
		counter = EEPROM_u8ReadDataByte(0x03FF);
	}
	
	
	UART_voidSendStringSynch("***** ");
	UART_voidSendStringSynch("The number of current users: ");
	UART_voidSendNumberSynch(counter);
	UART_voidSendDataSynch(' ');
	while(1){
		UART_voidSendStringSynch("1. Enter new user name. ");
		UART_voidSendStringSynch("2. Sign In. ");
		UART_voidSendStringSynch("3. Edit current data. ");
		UART_voidSendStringSynch("4. Show current data. ");
		UART_voidSendStringSynch("Choose a choice: ");
		UART_u8ReceiveDataSynch(&choose);			//enter '+' after you insert your choice
		UART_voidSendDataSynch(choose);
		UART_voidSendDataSynch(' ');
		switch(choose){
			case '1':
				new();
				break;
			case '2':
				SignIn();
				if(lock == 2)
					return 0;	//Close the application		/* needs update */
				if(lock == 1)
					Light();
				break;
			case '3':
				Edit();
				break;
			case '4':
				Show();
			
		}
	}
	return 0;

}


