/*
 * IMT project.c
 *
 * Created: 8/18/2020 4:18:16 PM
 * Author : EGYPT_LAPTOP
 */ 

#include"MCAL/UART.h"
#include <util/delay.h>

void __vector_13(void) __attribute__((signal));			//RX interrupt
void __vector_13(void){
	
	
}


int main(void)
{	
	u8 x ;
    /* Replace with your application code */
	UART_voidInit();
	
	UART_voidSendString("Enter a character: ");
 	
    while (1) 
    {
		x = UART_u8ReceiveChar();
		UART_voidSendChar(x);
		
    }
}

