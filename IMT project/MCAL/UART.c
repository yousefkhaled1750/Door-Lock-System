/*
 * UART.c
 *
 * Created: 8/18/2020 6:42:38 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#include "UART.h"
u8 flag = 0;



void UART_voidInit(void){
	//SET_BIT(SREG,7);	
	UBRRL = 51;		//baudrate 9600 for 8MHz
	UCSRB = 0x18;	//Enable RX , TX only without interrupts
	UCSRC = 0x86;	//8-bit data
}

void UART_voidSendChar(u8 data){
	
	while(GET_BIT(UCSRA,UDRE) == 0);
	UDR = data;
	while(GET_BIT(UCSRA,TXC) == 0);	//wait until data is transmitted
	SET_BIT(UCSRA,TXC);
}

u16 UART_u8ReceiveChar(void){
	
	while(GET_BIT(UCSRA,RXC)==0);
	
	SET_BIT(UCSRA,RXC);
	return UDR;
}

void UART_voidSendString(u8* str){
	u8 i = 0;
	do{	
		UART_voidSendChar(str[i]);
		i++;
	}while(str[i] != '\0');
	
}

void UART_voidSendNumber(u32 Num);

void UART_voidReceiveString(u8* str){
	
	u8 i = 0;
	while(1){
		str[i] = UART_u16ReceiveChar();
		if(str[i]=='\0'){
			break;
		}
		i++;
	}
	str[++i] = '\0';
}