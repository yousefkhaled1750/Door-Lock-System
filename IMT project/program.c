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
#include "TIMER_Interface.h"//edited
#include "LIB/STD_types.h"
#include "util/delay.h"


extern struct user users[10] = {0};	//initialize the structures with 0
static u8 address=0;
extern u8 counter = 0;
extern u8 lock = 0;





void new(void){
	if(counter<MAX_USER){		//the max number is 10
		Buffer[counter] = users[counter].name;	//set buffer pointer to the pointer of the struct member so it gets stored in it
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
	
	}else{
		UART_voidSendStringSynch("****No Space For New Users!****");
		UART_voidSendStringSynch(" You can edit the data of a current user. ");
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
	label1:
	while(trials<3)
	{
		
		UART_voidSendStringSynch("Enter Your Password: ");
		UART_voidReceiveNumberSynch(&password_check);
		if(password_check==users[ID].password)	
		{	
			UART_voidSendStringSynch(" |***Correct Password***| ");
			DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW);	//turn off the buzzer
			DIO_voidSetPinValue(LED_PORT, PASSWORD_LED, DIO_LOW);	//turn off the wrong password led
			DIO_voidSetPinValue(SOL_PORT,SOL_PIN, DIO_HIGH);
			_delay_ms(5000);
			DIO_voidSetPinValue(SOL_PORT, SOL_PIN, DIO_LOW);
			lock=1;
			break;
		}else{
			trials++;
			if(trials>2){
				goto label1;
			}
			UART_voidSendStringSynch("Not Correct! ");
			DIO_voidSetPinValue(LED_PORT, PASSWORD_LED, DIO_HIGH);	//turn on the wrong password
			label:
			UART_voidSendStringSynch(" 1. Try Again ");
			UART_voidSendStringSynch(" 2. back to menu ");
			UART_u8ReceiveDataSynch(&choose);
			if(choose == '1'){	continue;}	//repeat the loop to enter again the password
			else if(choose == '2'){ return; }	//close the function and get back to main menu
			else{
				UART_voidSendStringSynch(" choose a valid choice! ");
				goto label;
			}
			
		}

	}


	if(lock==0&&trials>=3)
	{
		UART_voidSendStringSynch("WARNING!! you are out of trials. ");
		DIO_voidSetPinValue(BUZZER_PORT,BUZZER_PIN, DIO_HIGH);	//turn on the buzzer
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
						Buffer[id] = users[id].name;	//to point at the name array so it edits the struct member
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
	
	UART_voidSendStringSynch("Welcome to our system! ");
	while(1)
	{
		UART_voidSendStringSynch("1. Toggle Red Light.		2. Toggle Blue Light.		3. Control the Fan.		4. Exit. ");
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
				//case 3 edited
				fan();
				break;
			case '4':	
				DIO_voidSetPortValue(LED_PORT, 0x00);
				TIMER0_VidPWMDutyCycle(STOP);	//turn off the DC fan
				return;
		}
	}
	
}

void fan(void){
	u8 choose;
	TIMER0_VidPWMInit();
	while(1){
		UART_voidSendStringSynch("1.speed max .		2. speed 50% .		3. speed 25%.		4.stop.			5. back to menu. ");
		UART_voidSendStringSynch("Your Choice: ");
		UART_u8ReceiveDataSynch(&choose);
		switch(choose)
		{
			case '1':
			TIMER0_VidPWMDutyCycle(SPEED_MAX);
			break;
			case '2':
			TIMER0_VidPWMDutyCycle(SPEED_50);
			break;
			case '3':
			TIMER0_VidPWMDutyCycle(SPEED_25);
			break;
			case '4':
			TIMER0_VidPWMDutyCycle(STOP);
			break;
			case '5':
			return;
		}
	}
}

void MovToStruct(void){
	u8 i = 0;
	for(i = 0; i<counter; i++){
		users[i].password = EEPROM_u8SearchForPassword(i);
		EEPROM_u8SearchForName(users[i].name,i);
	} 
}
