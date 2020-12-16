/*
 * program.c
 *
 * Created: 12/16/2020 5:53:19 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 

#include "MCAL/UART.h"
#include "program.h"
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
	UART_voidReceiveStringSynch(*(Buffer+counter), MAX_NAME_SIZE);
	users[counter].name = *(Buffer+counter);
	UART_voidSendDataSynch(' ');
	
	UART_voidSendStringSynch("Enter Your Password: ");
	UART_voidReceiveNumberSynch(pass+counter);
	users[counter].password = pass[counter];
	UART_voidSendDataSynch(' ');
	
	UART_voidSendStringSynch("Your ID is ");
	UART_voidSendDataSynch(counter + '0');
	UART_voidSendDataSynch(' ');
	
	counter++;
}
void SignIn(void);
void Light();
void Edit(){
	u8 id, choose;
	//u32 pass;
	
	UART_voidSendStringSynch("Enter Your ID ");
	UART_u8ReceiveDataSynch(&id);
	id -= '0';
	UART_voidSendDataSynch(' ');
	
	UART_voidSendStringSynch("Enter the Password: ");
	UART_voidReceiveNumberSynch(&pass);
	UART_voidSendDataSynch(' ');
	
	if(pass == users[id].password)
	{
		UART_voidSendStringSynch("1. Edit Your User Name.	2. Edit Your Password.	 3. exit the edit. ");
		UART_voidSendStringSynch("Choose a choice: ");
		UART_u8ReceiveDataSynch(&choose);
		UART_voidSendDataSynch(' ');
		
		switch(choose){
			case '1':
				UART_voidSendStringSynch("Enter Your New User Name: ");
				UART_voidReceiveStringSynch(*(Buffer+id), MAX_NAME_SIZE);
				users[id].name = *(Buffer+id);
				UART_voidSendDataSynch(' ');
				break;
			case '2':
				UART_voidSendStringSynch("Enter Your New Password: ");
				UART_voidReceiveNumberSynch(pass+id);
				users[id].password = pass[id];
				UART_voidSendDataSynch(' ');
				break;
			case '3':
				return;
		}
	}
	else
	{
		UART_voidSendStringSynch("Wrong Password!");
	}
	
}
void Show(){
	u8 id;
	//UART_voidSendDataSynch('\n');
	
	UART_voidSendStringSynch("Enter Your ID ");
	UART_u8ReceiveDataSynch(&id);
	id -= '0';
	UART_voidSendDataSynch(' ');
	
	UART_voidSendStringSynch("Your User Name: ");
	UART_voidSendStringSynch(users[id].name);
	UART_voidSendDataSynch(' ');
	
	UART_voidSendStringSynch("Your Password: ");
	UART_voidSendNumberSynch(users[id].password);
	UART_voidSendDataSynch(' ');
	
}