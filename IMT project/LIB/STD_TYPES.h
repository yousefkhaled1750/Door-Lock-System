/*
 * STD_TYPES.h
 *
 * Created: 7/22/2020 8:10:38 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef double f64;

typedef union{
	struct{
		u8 B0 : 1;
		u8 B1 : 1;
		u8 B2 : 1;
		u8 B3 : 1;
		u8 B4 : 1;
		u8 B5 : 1;
		u8 B6 : 1;
		u8 B7 : 1;
		}Bit;
		
		u8 Byte;
	
	}Register;



#endif /* STD_TYPES_H_ */