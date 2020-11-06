/*
 * Bit_math.h
 *
 * Created: 7/22/2020 6:20:02 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BITNO)  (VAR |= (1<<BITNO))
#define CLR_BIT(VAR,BITNO)	(VAR &= ~(1<<BITNO))
#define TOG_BIT(VAR,BITNO)	(VAR ^= (1<<BITNO))
#define GET_BIT(VAR,BITNO)	(1&(VAR>>BITNO))
#define SET_VAL(VAR,BITNO,VALUE)	(VAR |= (VALUE<<BITNO))



#endif /* BIT_MATH_H_ */