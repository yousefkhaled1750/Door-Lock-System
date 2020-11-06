/*
 * DIO_REG.h
 *
 * Created: 7/22/2020 10:03:57 PM
 *  Author: Yusef Khaled Abu Elnaga
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_

#include "../LIB/STD_TYPES.h"

/* PORTA Registers */
#define PORTA *((volatile u8*) 0x3B) 
#define DDRA *((volatile u8*) 0x3A)
#define PINA *((volatile u8*) 0x39)

/* PORTB Registers */
#define PORTB *((volatile u8*) 0x38)
#define DDRB *((volatile u8*) 0x37)
#define PINB *((volatile u8*) 0x36)

/* PORTC Registers */
#define PORTC *((volatile u8*) 0x35)
#define DDRC *((volatile u8*) 0x34)
#define PINC *((volatile u8*) 0x33)

/* PORTD Registers */
#define PORTD *((volatile u8*) 0x32)
#define DDRD *((volatile u8*) 0x31)
#define PIND *((volatile u8*) 0x30)


#endif /* DIO_REG_H_ */