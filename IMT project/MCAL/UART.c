/*
 * UART.c
 *
 * Created: 8/18/2020 6:42:38 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#include "UART.h"




void UART_voidInit(void){
	u8  ucsrb, ucsrc;	
	ucsrb = ucsrb |(1<<TXEN | 1<<RXEN);		//Enable TX and RX.    //we didn't set the interrupts yet
	ucsrc = ucsrc |(1<<URSEL| 3<<UCSZ);		//select UCSRC and set the character size to 8 bit.
	
	UBRRL = 51;		//baudrate 9600 for 8MHz
	
	UCSRB = ucsrb;	//Enable RX , TX only without interrupts
	UCSRC = ucsrc;	//8-bit data
}


//For Polling transmission and reception
void UART_voidSendDataSynch(u8 Copy_u8Data){
	
	while(GET_BIT(UCSRA,UDRE) == 0);	//wait until the Data Registe Embty is set
	UDR = Copy_u8Data;
	while(GET_BIT(UCSRA,TXC) == 0);	//wait until data is transmitted
	SET_BIT(UCSRA,TXC);	//clear the flag of TX complete
}

void UART_u8ReceiveDataSynch(u8 *Copy_pu8Data){
	while(GET_BIT(UCSRA,RXC)==0);	//wait until there's data to be read in the receive buffer
	SET_BIT(UCSRA,RXC);				//clear the receive flag 
	*Copy_pu8Data = UDR;			//send the received character to the addressed variable
}

void UART_voidSendStringSynch(u8* Copy_pu8String){
	u8 counter = 0;
		while(Copy_pu8String[counter] != '\0'){
			
			UART_voidSendDataSynch(Copy_pu8String[counter]);
			counter++;
		}
		
	
}

void UART_voidSendNumberSynch(u32 Copy_u32Number){
	u8 SentChar;
	u32 y = 1;
	
	while(Copy_u32Number/(10*y) !=0){
		y*=10;
	}
	while(Copy_u32Number !=0){
		SentChar = (Copy_u32Number/y)+'0';
		UART_voidSendDataSynch(SentChar);
		Copy_u32Number %=y;
		y/=10;
	}
}

void UART_voidReceiveStringSynch(u8* Copy_pu8Data , u8 BufferSize){
	
	u8 counter = -1;
	do{
		counter++;
		UART_u8ReceiveDataSynch(Copy_pu8Data+counter);
		UART_voidSendDataSynch(Copy_pu8Data[counter]);
	}while(Copy_pu8Data[counter] != '+' && counter < BufferSize-1 );				//loop until Enter is pressed and is less than the last element of the buffer
	Copy_pu8Data[counter] = '\0';			//put the null character at the last element of the buffer
}

void UART_voidReceiveNumberSynch(u32 *Copy_pu32Number){
	u8 Buffer[10];
	u8 numlen = -1;
	u8 counter = 0;
	u32 number = 0;
	u32 decimal = 1;
	u8 temp;
	do{		//receive the number and put it into a buffer
		numlen++;
		UART_u8ReceiveDataSynch(&(Buffer[numlen]));
		UART_voidSendDataSynch(Buffer[numlen]);
		
	}while(Buffer[numlen] != '+' && numlen< 10);		//the last element storing Enter char.
	
	for( ;counter<=numlen/2;counter++){	//swap the buffer element	as it is stored inversely
		temp = Buffer[numlen - counter-1];
		Buffer[numlen - counter - 1] = Buffer[counter] - '0';
		Buffer[counter] = temp - '0';
		
	}
	for(counter = 0; counter<numlen; counter++){
		number = number + Buffer[counter]*decimal;
		decimal *= 10;
		//UART_voidSendNumberSynch(number);	
	}
	
	*Copy_pu32Number = number;
	
}



