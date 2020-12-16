/*
 * program.c
 *
 * Created: 12/16/2020 5:53:19 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 

#include "MCAL/UART.h"
#include "LIB/STD_types.h"

struct user
{
	u8 *name;
	u32 password;

};
struct user users[10] = {0};

u8 counter = 0;
u8 lock = 0;
u8 *Buffer[10];
u32 pass[10];

void new(void){
	//UART_voidSendDataSynch('\n');
	
	UART_voidSendStringSynch("Enter Your User Name: ");
	UART_voidReceiveStringSynch(*(Buffer+counter), sizeof(users[counter].name));
	users[counter].name = *(Buffer+counter);
	
	UART_voidSendStringSynch("Enter Your Password: ");
	UART_voidReceiveNumberSynch(pass+counter);
	users[counter].password = pass[counter];
	
	UART_voidSendStringSynch("Your ID is ");
	UART_voidSendDataSynch(counter + '0');
	counter++;
}
void SignIn(void);
void Light();
void Edit();
void Show(){
	u8 id;
	//UART_voidSendDataSynch('\n');
	
	UART_voidSendStringSynch("Enter Your ID ");
	UART_u8ReceiveDataSynch(&id);
	id -= '0';
	UART_voidSendStringSynch("Your User Name: ");
	UART_voidSendStringSynch(users[id].name);
	UART_voidSendDataSynch('\n');
	UART_voidSendStringSynch("Your Password: ");
	UART_voidSendNumberSynch(users[id].password);
	
}