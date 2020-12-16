/*
 * program.c
 *
 * Created: 12/16/2020 5:53:19 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 

#include "MCAL/UART.h"
#include "program.h"
#include "LIB/STD_types.h"
#include "util/delay.h"

extern struct user users[10] = {0};

extern u8 counter = 0;
extern u8 lock = 0;
void new(void){
	//UART_voidSendDataSynch('\n');
	
	Buffer[counter] = users[counter].name;
	UART_voidSendStringSynch("Enter Your User Name: ");
	UART_voidReceiveStringSynch(*(Buffer+counter), MAX_NAME_SIZE);
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
void SignIn(void)
{
	u8 i;
	u8 ID;
	u32 password_check;
	u8 trials=0;
	UART_voidSendStringSynch("Enter Your User ID: ");
	UART_u8ReceiveDataSynch(&ID);
	ID -= '0';
	while(trials<3)
	{
		
		UART_voidSendStringSynch("Enter Your Password: ");
		UART_voidReceiveNumberSynch(&password_check);
		
		if(password_check==users[ID].password)	
		{	
			UART_voidSendStringSynch(" |***Correct Password***| ");
			lock=1;
			break;
		}else{
			UART_voidSendStringSynch("Not Correct! ");
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1, DIO_HIGH);
			_delay_ms(2000);
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1, DIO_LOW);
			trials++;
		}

	}


	if(lock==0&&trials>=3)
	{
		UART_voidSendStringSynch("WARNING!! you are out of trials. ");
		//DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0, DIO_HIGH);	//turn on the buzzer
		lock = 2;
	}
}

void Edit(){
	u8 id, choose, key;
	u32 pass;
	
	UART_voidSendStringSynch("Enter Your ID ");
	UART_u8ReceiveDataSynch(&id);
	id -= '0';
	UART_voidSendDataSynch(' ');
	
	UART_voidSendStringSynch("Enter the Password: ");
	UART_voidReceiveNumberSynch(&pass);
	UART_voidSendDataSynch(' ');
	
	if(pass == users[id].password)
	{		
		key = 1;
		while(key ==1){
			UART_voidSendStringSynch("1. Edit Your User Name.	2. Edit Your Password.	 3. exit the edit. ");
			UART_voidSendStringSynch("Choose a choice: ");
			UART_u8ReceiveDataSynch(&choose);
			UART_voidSendDataSynch(' ');
		
			switch(choose){
				case '1':
					Buffer[id] = users[id].name;
					UART_voidSendStringSynch("Enter Your New User Name: ");
					UART_voidReceiveStringSynch(*(Buffer+id), MAX_NAME_SIZE);
					UART_voidSendDataSynch(' ');
					break;
				case '2':
					UART_voidSendStringSynch("Enter Your New Password: ");
					UART_voidReceiveNumberSynch(&pass);
					users[id].password = pass;
					UART_voidSendDataSynch(' ');
					break;
				case '3':
					key = 0;
					break;
			}
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

void Unlock(){
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN2, DIO_HIGH);
	_delay_ms(3000);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN2, DIO_LOW);
}

void Light(){
	u8 choose;
	DIO_voidSetPortDirection(DIO_PORTA, DIO_OUTPUT);
	
	UART_voidSendStringSynch("Welcome to our system! ");
	while(1)
	{
		UART_voidSendStringSynch("1. Toggle Red Light.		2. Toggle Blue Light.		3. Toggle the Fan.		4. Exit. ");
		UART_voidSendStringSynch("Your Choice: ");
		UART_u8ReceiveDataSynch(&choose);

		switch(choose){
	
			case '1':	
				DIO_voidSetPinValue(LED_PORT,RED_LED, DIO_TOGGLE);
				break;
			case '2':
				DIO_voidSetPinValue(LED_PORT,BLUE_LED, DIO_TOGGLE);
				break;
			case '3':
				DIO_voidSetPinValue(LED_PORT,FAN, DIO_TOGGLE);
				break;
			case '4':	
				DIO_voidSetPortValue(LED_PORT, 0x00);
				return;
		}
	}
	
}