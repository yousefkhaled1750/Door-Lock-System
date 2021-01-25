/*
 * DIO_INT.h
 *
 * Created: 7/22/2020 10:47:20 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef DIO_INT_H_
#define DIO_INT_H_
#include "DIO_REG.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/Bit_math.h"

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_OUTPUT 1
#define DIO_INPUT  0

#define DIO_TOGGLE 2
#define DIO_HIGH  1
#define DIO_LOW	  0

/* set the direction of the pin in a port chosen by the user */
void DIO_voidSetPinDirection(u8 Copy_u8PortNB, u8 Copy_u8PinNB, u8 Copy_u8PinDirection);

/* set the value of a pin in a port chosen by the user */
void DIO_voidSetPinValue(u8 Copy_u8PortNB, u8 Copy_u8PinNB, u8 Copy_u8PinValue);

/* get the value of a pin in a port chosen by the user */
u8 DIO_u8GetPinValue(u8 Copy_u8PortNB, u8 Copy_u8PinNB);

/* set the direction of the port chosen by the user */
void DIO_voidSetPortDirection(u8 Copy_u8PortNB,u8 Copy_u8PortDirection);

/* set the value of a port chosen by the user */
void DIO_voidSetPortValue(u8 Copy_u8PortNB, u8 Copy_u8PinValue);

/* get the value of a port chosen by the user */
u8 DIO_u8GetPortValue(u8 Copy_u8PortNB);




#endif /* DIO_INT_H_ */