/*
 * ADC_PROG.c
 *
 * Created: 8/15/2020 2:44:51 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 

#include "ADC.h"

void ADC_voidInit(){
	SET_BIT(ADCSRA, ADEN);
	//SET_BIT(ADCSRA, ADIE);
	SET_VAL(ADCSRA, ADPS, 5);	//prescaler= 64 --> Freq = 125,000
	SET_BIT(SREG, 7);	
	SET_VAL(ADMUX, REFS, AVCC);
}

void ADC_StartConversion(u8 ADC_PinNo){
	CLR_BIT(ADMUX, 0);
	CLR_BIT(ADMUX, 1);
	CLR_BIT(ADMUX, 2);
	CLR_BIT(ADMUX, 3);
	CLR_BIT(ADMUX, 4);
	SET_VAL(ADMUX, MUX, ADC_PinNo);
	SET_BIT(ADCSRA, ADSC);
}