/*
 * program.h
 *
 * Created: 12/16/2020 6:34:00 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef PROGRAM_H_
#define PROGRAM_H_
#include "LIB/STD_TYPES.h"
#define MAX_NAME_SIZE	20
#define MAX_USER	10
#define F_CPU	8000000UL

#define RED_LED DIO_PIN3
#define BLUE_LED DIO_PIN4
#define LED_PORT DIO_PORTA

#define BUZZER_PIN	DIO_PIN2
#define BUZZER_PORT DIO_PORTA
#define PASSWORD_LED	DIO_PIN1

#define SOL_PIN		DIO_PIN0
#define SOL_PORT	DIO_PORTA	

#define FAN_PIN DIO_PIN3//edited
#define FAN_PORT DIO_PORTB//edited
#define SPEED_MAX 255 //edited
#define SPEED_50 128 //edited
#define SPEED_25 64 //edited
#define STOP 0 //edited

struct user
{
	u32 password;
	u8 name[MAX_NAME_SIZE];
	

};
struct user users[MAX_USER] ;

//used for storing the choices of menus
u8 choose;
//counter for the user data that will be stored in the struct
u8 counter ;
//To determine whether sign in was successful or not
u8 lock ;
//Array of pointers to allocate the strings (name) then send it to the struct
u8 *Buffer[10];
//Array of Integers to store the passwords then send it to the struct
u32 pass[10];

//Called to register new user
void new(void);
//to sign in for an already existed user
void SignIn(void);
//Called after successful sign in where it can control the house
void Light(void);
//to edit the user data using ID
void Edit(void);
//to show the data of a user
void Show(void);
//used to unlock the door lock 
void Unlock(void);
//used to control the fan
void fan(void);

void EEPROM_voidWriteName(u8* Copy_pu8String,u8 user_id);
void EEPROM_voidWriteId(u8 user_id);
void EEPROM_voidWritePassword(u32 Copy_u32Number,u8 user_id);
u32 EEPROM_u8SearchForPassword(u8 user_id);
u8 EEPROM_u8SearchForName(u8*name,u8 user_id);
void MovToStruct(void);



#endif /* INCFILE1_H_ */
