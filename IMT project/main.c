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
	UART_voidInit();
	while(1){
		UART_voidSendStringSynch("Choose a choice: ");
		UART_u8ReceiveDataSynch(&choose);
		UART_voidSendDataSynch(choose);
		UART_voidSendDataSynch(' ');
		switch(choose){
			case '1':
				new();
				break;
			case '2':
				//SignIn();
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


