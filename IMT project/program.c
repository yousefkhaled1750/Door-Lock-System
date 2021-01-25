/*
 * program.c
 *
 * Created: 12/16/2020 5:53:19 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 

/* Needs the Free() function to delete a user in the middle of the array */
/* Needs the buzzer */
/* needs the DC motor with PWM and ADC in addition to relay and transistor */
/* move the project to the repo*/
/*TWI and EEPROM */

#include "MCAL/UART.h"
#include "program.h"
#include "eeprom.h"
#include "LIB/STD_types.h"
#include "util/delay.h"


extern struct user users[10] = {0};
u8 address=0;
extern u8 counter = 0;
extern u8 lock = 0;





void new(void){
	if(counter<MAX_USER){		//the max number is 10
		Buffer[counter] = users[counter].name;
		UART_voidSendStringSynch("Enter Your User name: ");
		UART_voidReceiveStringSynch(*(Buffer+counter), MAX_NAME_SIZE);

		UART_voidSendDataSynch(' ');
	
		UART_voidSendStringSynch("Enter Your Password: ");
		UART_voidReceiveNumberSynch(pass+counter);
		users[counter].password = pass[counter];
		UART_voidSendDataSynch(' ');
	
		UART_voidSendStringSynch("Your ID is ");
		UART_voidSendDataSynch(counter + '0');
		UART_voidSendDataSynch(' ');
	
		EEPROM_voidWriteId(counter);
		EEPROM_voidWriteName(*(Buffer),counter);	//the pointer of buffer points at first element of the struct
		EEPROM_voidWritePassword(pass[counter],counter);
		counter++;	//increment before sending counter to 0x03FF to indicate the number of user as number of users = id + 1
		EEPROM_voidSendDataByte(0x03FF, counter);	//Put the number of users in the last address of eeprom
	
	
		/******//*
		EEPROM_voidSendDataByte(0,'a');
		/******/
	}
}




void EEPROM_voidWriteName(u8* Copy_pu8String,u8 user_id){
	u8 i=0;
	while(Copy_pu8String[i] != '\0'){

		EEPROM_voidSendDataByte(user_id*50+5+i,Copy_pu8String[i]);
		i++;
		address++;
	}

	EEPROM_voidSendDataByte(user_id*50+5+i,'\0');//edited

}



void EEPROM_voidWriteId(u8 user_id){
		EEPROM_voidSendDataByte(user_id*50,user_id);
		address++;
		}



void EEPROM_voidWritePassword(u32 Copy_u32Number,u8 user_id)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		EEPROM_voidSendDataByte(user_id*50+1+i,((Copy_u32Number>>(i*8))&0xff));
		address++;
	}
	
}




/*u8 EEPROM_u8SearchForStartData(u8 id_search)//return address of id
{
	u8 i=0;
	u8 found=0;
	u8 data;
	u8 id;

	for(i=0;i<address;i++)
	{
		data=EEPROM_u8ReadDataByte(i);

		if(data=='=')
		{
			id=EEPROM_u8ReadDataByte(i+1);
			if(id==id_search)
			{
			found=1;
			return (i+1);
			}
	    }
	if (found==0)
	{
		return '-';
	}
}
*/




u32 EEPROM_u8SearchForPassword(u8 user_id)//return password bta3 el user
{
	u32 start=50*user_id+1;
	u8 j;
	u8 end_round=start+4;
	u32 old_password;
	u32 password=0;
	u8 count=0;
	for(j=start;j<=end_round;j++)
	{
		old_password=EEPROM_u8ReadDataByte(j);//hayt3melo shift w hyetkteb sah
		password=password+(old_password<<(count*8));
		count++;
	}
	return password;
}




u8 EEPROM_u8SearchForName(u8*name,u8 user_id)//bet5zen el name w btraga3 el size bta3o w bta5od address id
{
	u8 start=50*user_id+5;	//address of 1st char
	u8 i;
	u8 j=0;
	u8 end_count;
	end_count=EEPROM_u8ReadDataByte(start);		
	for(i=start;end_count!='\0';i++)
	{
	    name[j]=end_count;
		end_count=EEPROM_u8ReadDataByte(i+1);//edited
		j++;
	}
	name[j]='\0';//edited	
	return j;
}





void SignIn(void)
{
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
		users[ID].password==EEPROM_u8SearchForPassword(ID);
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
	if(id<counter){
		UART_voidSendStringSynch("Enter the Password: ");
		UART_voidReceiveNumberSynch(&pass);
		UART_voidSendDataSynch(' ');
		users[id].password=EEPROM_u8SearchForPassword(id);
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
						EEPROM_voidWriteName(*(Buffer+id),id);
						UART_voidSendDataSynch(' ');
						break;
					case '2':
						UART_voidSendStringSynch("Enter Your New Password: ");
						UART_voidReceiveNumberSynch(&pass);
						users[id].password = pass;
						EEPROM_voidWritePassword(pass,id);
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
	else{
		UART_voidSendStringSynch("We Don't have this ID! ");
	}
}





void Show(){
	u8 id;
	u8 z;
	UART_voidSendStringSynch("Enter Your ID ");
	UART_u8ReceiveDataSynch(&id);
	UART_voidSendDataSynch(id);	
	id -= '0';
	UART_voidSendDataSynch(' ');
	
	
	
	
		
	if(id < counter){
		
			UART_voidSendStringSynch("Your User Name: ");

			z=EEPROM_u8SearchForName(users[id].name,id);
			UART_voidSendStringSynch(users[id].name);
			UART_voidSendDataSynch(' ');
		
			UART_voidSendStringSynch("Your Password: ");

			users[id].password=EEPROM_u8SearchForPassword(id);

			UART_voidSendNumberSynch(users[id].password);
			UART_voidSendDataSynch(' ');
	}else{
		UART_voidSendStringSynch("We Don't Have this ID ");
	}
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

