/*
 * IMT project.c
 *
 * Created: 8/18/2020 4:18:16 PM
 * Author : EGYPT_LAPTOP
 */ 
#include "program.h"
#include "MCAL/UART.h"



int main (void)
{
	u8 choose;
	DIO_voidSetPortDirection(DIO_PORTC, DIO_OUTPUT);
	UART_voidInit();
	while(1){
		UART_voidSendStringSynch("1. Enter new user name. ");
		UART_voidSendStringSynch("2. Sign In. ");
		UART_voidSendStringSynch("3. Edit current data. ");
		UART_voidSendStringSynch("4. Show current data. ");
		UART_voidSendStringSynch("Choose a choice: ");
		UART_u8ReceiveDataSynch(&choose);
		UART_voidSendDataSynch(choose);
		UART_voidSendDataSynch(' ');
		switch(choose){
			case '1':
				new();
				break;
			case '2':
				SignIn();
				if(lock == 2)
					return 0;
				if(lock == 1){
					Unlock();		
					Light();
				}
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


