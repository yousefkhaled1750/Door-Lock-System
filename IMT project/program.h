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
#define F_CPU	8000000UL

#define RED_LED DIO_PIN3
#define BLUE_LED DIO_PIN4
#define FAN	DIO_PIN2
#define LED_PORT DIO_PORTA

struct user
{
	u8 name[10];
	u32 password;

};
struct user users[10] ;

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



#endif /* INCFILE1_H_ */