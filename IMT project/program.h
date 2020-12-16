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

struct user
{
	u8 name[10];
	u32 password;

};
struct user users[10] ;

u8 counter ;
u8 lock ;
u8 *Buffer[10];
u32 pass[10];


void new(void);
void SignIn(void);
void Light(void);
void Edit(void);
void Show(void);



#endif /* INCFILE1_H_ */