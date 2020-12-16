/*
 * UART.h
 *
 * Created: 8/18/2020 4:19:00 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef UART_H_
#define UART_H_
#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "DIO_INT.h"

#define F_CPU 8000000
//BAUD = fosc/16(UBBR+1) --> UBBR = fosc/(16*BAUD) - 1	--> Asynchornous 
//BAUD = fosc/2(UBBR+1) --> UBBR = fosc/(2*BAUD) - 1	-->  synchronous
#define UBRRL *((volatile u8*) 0x29)
#define UCSRB *((volatile u8*) 0x2A)
#define UCSRA *((volatile u8*) 0x2B)
#define UDR   *((volatile u8*) 0x2C)
#define UCSRC *((volatile u8*) 0x40)
#define UBRRH *((volatile u8*) 0x40)
#define SREG  *((volatile u8*) 0x5F)


//UCSRA
#define RXC		7	//after receive
#define TXC		6	//after transmit
#define UDRE	5	//UDR empty
#define FE		4	//always set this bit to zero
#define DOR		3	//always set this bit to zero
#define PE		2`	//always set this bit to zero
#define U2X		1	//double the speed and reduce the divisor from 16 to 8 in BAUD
#define MPCM	0	//multi processor

//UCSRB
#define RXIE	7
#define TXIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1	//8th bit must be read before UDR
#define TXB8	0	//8th bit must be written before UDR

//UCSRC
#define URSEL	7	//UCSRC = 1, UBRRH = 0
#define UMSEL	6	//Asynch = 0, Synch = 1
#define UPM		4	//2 bits for parity 
#define USBS	3	//1-bit stop = 0, 2-bit stop =1
#define UCSZ	1	//2 bits with UCSZ2	for character size
#define UCPOL	0	//used with synch mode




void UART_voidInit(void);

void UART_voidSendDataSynch(u8 Copy_u8Data);

void UART_u8ReceiveDataSynch(u8 *Copy_pu8Data);

void UART_voidSendStringSynch(u8* Copy_pu8String);

void UART_voidSendNumberSynch(u32 Copy_u32Number);

void UART_voidReceiveStringSynch(u8* Copy_pu8Data , u8 BufferSize);

void UART_voidReceiveNumberSynch(u32 *Copy_pu32Number);

#endif /* UART_H_ */