#include"LIB/Bit_math.h"
#include"LIB/STD_TYPES.h"
#include "TIMER_Register.h"
void TIMER0_VidPWMInit(void)
{
	//TIMER0 FAST PWM mode
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	//TIMER0 FAST PWM CLEAR ON CTC
		CLR_BIT(TCCR0,4);
		SET_BIT(TCCR0,5);

	//TIMER0 prescaler 64
	SET_BIT(TCCR0,0);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}
void TIMER0_VidPWMDutyCycle(u8 u8_OCR0)
{
	OCR0=u8_OCR0;
}
