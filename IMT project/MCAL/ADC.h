/*
 * ADC.h
 *
 * Created: 8/15/2020 1:14:09 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO_INT.h"


#define VREF	5
#define RES		1024
#define F_CPU	8000000
#define prescaler	64
#define ANLG(ADC)	((ADC*VREF)/RES)
#define DIGT(VIN)	((VIN * RES)/VREF)


#define ADCL	*((volatile u8*) 0x24)
#define ADCH	*((volatile u8*) 0x25)
#define ADCSRA	*((volatile u8*) 0x26)
#define ADMUX	*((volatile u8*) 0x27)
#define SFIOR	*((volatile u8*) 0x50)
#define SREG	*((volatile u8*) 0x5F)

#define AVCC	1
#define AREF	0
#define INTREF	3

//ADMUX
#define REFS	6	//reference voltage 1:4
#define ADLAR	5	//Left Adjustment
#define MUX		0	//input selection

//ADCSRA
#define ADEN	7	//ADC enable
#define ADSC	6	//start conversion
#define	ADATE	5	//auto trigger
#define ADIF	4	//interrupt flag
#define ADIE	3	//interrupt enable
#define ADPS	0	//prescaler 1:8 

//SFIOR
#define SFIOR	5	//auto trigger source

void ADC_voidInit();
void ADC_StartConversion(u8 ADC_PinNo);


#endif /* ADC_H_ */