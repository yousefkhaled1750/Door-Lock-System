/*
 * DIO_PROG.c
 *
 * Created: 7/22/2020 11:09:05 PM
 *  Author: EGYPT_LAPTOP
 */ 

#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "DIO_INT.h"
#include "DIO_REG.h"


void DIO_voidSetPinDirection(u8 Copy_u8PortNB, u8 Copy_u8PinNB, u8 Copy_u8Direction)
{
	/*input validation */
	if( (Copy_u8PortNB> DIO_PORTD) || (Copy_u8PinNB > DIO_PIN7) )
	{
		#warning "You Entered invalid inputs" 
		return ;
	}
	else
	{
		/* API Logic */
		switch(Copy_u8Direction){
			case DIO_INPUT:
			switch (Copy_u8PortNB){
				case DIO_PORTA:
				CLR_BIT(DDRA,Copy_u8PinNB);
				break;

				case DIO_PORTB:
				CLR_BIT(DDRB,Copy_u8PinNB);
				break;

				case DIO_PORTC:
				CLR_BIT(DDRC,Copy_u8PinNB);
				break;

				case DIO_PORTD:
				CLR_BIT(DDRD,Copy_u8PinNB);
				break;
			}
			break;
			case DIO_OUTPUT:
			switch (Copy_u8PortNB){
				case DIO_PORTA:
				SET_BIT(DDRA,Copy_u8PinNB);
				break;

				case DIO_PORTB:
				SET_BIT(DDRB,Copy_u8PinNB);
				break;

				case DIO_PORTC:
				SET_BIT(DDRC,Copy_u8PinNB);
				break;

				case DIO_PORTD:
				SET_BIT(DDRD,Copy_u8PinNB);
				break;
			}
			break;

		}
	}
}

void DIO_voidSetPinValue(u8 Copy_u8PortNB, u8 Copy_u8PinNB, u8 Copy_u8Value)
{
	/*input validation */
	if( (Copy_u8PortNB> DIO_PORTD) || (Copy_u8PinNB > DIO_PIN7) )
	{
		#warning "You Entered invalid inputs"
		return ;
	}
	else
	{
		/* API Logic */
		switch(Copy_u8Value){
			case DIO_LOW:
				switch (Copy_u8PortNB){
					case DIO_PORTA:
					CLR_BIT(PORTA,Copy_u8PinNB);
					break;

					case DIO_PORTB:
					CLR_BIT(PORTB,Copy_u8PinNB);
					break;

					case DIO_PORTC:
					CLR_BIT(PORTC,Copy_u8PinNB);
					break;

					case DIO_PORTD:
					CLR_BIT(PORTD,Copy_u8PinNB);
					break;
				}
				break;
			case DIO_HIGH:
				switch (Copy_u8PortNB){
					case DIO_PORTA:
					SET_BIT(PORTA,Copy_u8PinNB);
					break;

					case DIO_PORTB:
					SET_BIT(PORTB,Copy_u8PinNB);
					break;

					case DIO_PORTC:
					SET_BIT(PORTC,Copy_u8PinNB);
					break;

					case DIO_PORTD:
					SET_BIT(PORTD,Copy_u8PinNB);
					break;
				}
				break;
			case DIO_TOGGLE:
				switch (Copy_u8PortNB){
					case DIO_PORTA:
					TOG_BIT(PORTA,Copy_u8PinNB);
					break;

					case DIO_PORTB:
					TOG_BIT(PORTB,Copy_u8PinNB);
					break;

					case DIO_PORTC:
					TOG_BIT(PORTC,Copy_u8PinNB);
					break;

					case DIO_PORTD:
					TOG_BIT(PORTD,Copy_u8PinNB);
					break;
				}

		}
	}
}

u8 DIO_u8GetPinValue(u8 Copy_u8PortNB, u8 Copy_u8PinNB)
{
	u8 Local_u8PinValue;
	/*input validation */
	if( (Copy_u8PortNB> DIO_PORTD) || (Copy_u8PinNB > DIO_PIN7) )
	{
		#warning "You Entered invalid inputs"
		return 10;	/*any number else than 1 or 0 */
	}
	else
	{
		/* API Logic */


		switch (Copy_u8PortNB){
			case DIO_PORTA:
			Local_u8PinValue =	GET_BIT(DIO_PORTA,Copy_u8PinNB);
			break;

			case DIO_PORTB:
			Local_u8PinValue = GET_BIT(DIO_PORTB,Copy_u8PinNB);
			break;

			case DIO_PORTC:
			Local_u8PinValue = GET_BIT(DIO_PORTC,Copy_u8PinNB);
			break;

			case DIO_PORTD:
			Local_u8PinValue = GET_BIT(DIO_PORTD,Copy_u8PinNB);
			break;
		}

		return Local_u8PinValue;

	}
}

void DIO_voidSetPortDirection(u8 Copy_u8PortNB,u8 Copy_u8PortDirection){
	/* input validation */
	if(Copy_u8PortNB>DIO_PORTD ){
		#warning "You Entered invalid inputs"
		return;
	}
	else
	{
		switch(Copy_u8PortDirection){
			case DIO_HIGH:
			switch (Copy_u8PortNB){
				case DIO_PORTA: DDRA = 0xff; break;
				case DIO_PORTB: DDRB = 0xff; break;
				case DIO_PORTC: DDRC = 0xff; break;
				case DIO_PORTD: DDRD = 0xff; break;
			}
			break;

			case  DIO_LOW:
			switch (Copy_u8PortNB){
				case DIO_PORTA: DDRA = 0x00; break;
				case DIO_PORTB: DDRB = 0x00; break;
				case DIO_PORTC: DDRC = 0x00; break;
				case DIO_PORTD: DDRD = 0x00; break;
			}break;
		}
	}

}

/* set the value of a port chosen by the user */
void DIO_voidSetPortValue(u8 Copy_u8PortNB, u8 Copy_u8PinValue){
/* input validation */
	if(Copy_u8PortNB>DIO_PORTD ){
		#warning "You Entered invalid inputs"
		return;
	}
	else{
		switch(Copy_u8PortNB){
			case DIO_PORTA: PORTA = Copy_u8PinValue; break;
			case DIO_PORTB: PORTB = Copy_u8PinValue; break;
			case DIO_PORTC: PORTC = Copy_u8PinValue; break;
			case DIO_PORTD: PORTD = Copy_u8PinValue; break;
		}

	}
	
}

/* get the value of a port chosen by the user */
u8 DIO_u8GetPortValue(u8 Copy_u8PortNB){
	
	/* input validation */
	if(Copy_u8PortNB>DIO_PORTD ){
		#warning "You Entered invalid inputs"
		return;
	}
	else{
		switch(Copy_u8PortNB){
			case DIO_PORTA: return PINA; break;
			case DIO_PORTB: return PINB; break;
			case DIO_PORTC: return PINC; break;
			case DIO_PORTD: return PIND; break;
		}

	}
	
}