

#define SET_BIT(VAR,BITNO)  (VAR |= (1<<BITNO))
#define CLR_BIT(VAR,BITNO)	(VAR &= ~(1<<BITNO))
#define TOG_BIT(VAR,BITNO)	(VAR ^= (1<<BITNO))
#define GET_BIT(VAR,BITNO)	(1&(VAR>>BITNO))
#define SET_VAL(VAR,BITNO,VALUE)	(VAR |= (VALUE<<BITNO))

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



#define UBRRL *((volatile u8*) 0x29)
#define UCSRB *((volatile u8*) 0x2A)
#define UCSRA *((volatile u8*) 0x2B)
#define UDR   *((volatile u8*) 0x2C)
#define UCSRC *((volatile u8*) 0x40)
#define UBRRH *((volatile u8*) 0x40)
#define SREG  *((volatile u8*) 0x5F)


//UCSRA
#define RXC		7	//after receive
#define TXC		6	//after transmit
#define UDRE	5	//UDR empty
#define FE		4	//always set this bit to zero
#define DOR		3	//always set this bit to zero
#define PE		2`	//always set this bit to zero
#define U2X		1	//double the speed and reduce the divisor from 16 to 8 in BAUD
#define MPCM	0	//multi processor

//UCSRB
#define RXIE	7
#define TXIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1	//8th bit must be read before UDR
#define TXB8	0	//8th bit must be written before UDR

//UCSRC
#define URSEL	7	//UCSRC = 1, UBRRH = 0
#define UMSEL	6	//Asynch = 0, Synch = 1
#define UPM		4	//2 bits for parity 
#define USBS	3	//1-bit stop = 0, 2-bit stop =1
#define UCSZ	1	//2 bits with UCSZ2	for character size
#define UCPOL	0	//used with synch mode, when Asynch put 0




void UART_voidInit(void);

void UART_voidSendChar(u8 data);

u16 UART_u8ReceiveChar(void);

void UART_voidSendString(u8* str);

void UART_voidSendNumber(u32 Num);

void UART_voidReceiveString(u8* str);



void __vector_13(void) __attribute__((signal));			//RX interrupt
void __vector_13(void){
	
	UART_voidSendChar('M');
	f = UDR;
	UART_voidSendChar(f);
	SET_BIT(UCSRA, RXC);
}


int main(void)
{	
	u8 x ;
    /* Replace with your application code */
	UART_voidInit();
	
	UART_voidSendString("Enter a character: ");
 	
    while (1) 
    {
		x = UART_u8ReceiveChar();
		UART_voidSendChar(x);
		
    }
}





void UART_voidInit(void){
	SET_BIT(SREG,7);	
	UBRRL = 51;		//baudrate 9600 for 8MHz
	UCSRB = 0x98;	//Enable RX , TX only without interrupts
	UCSRC = 0x86;	//8-bit data
}

void UART_voidSendChar(u8 data){
	
	while(GET_BIT(UCSRA,UDRE) == 0);
	UDR = data;
	while(GET_BIT(UCSRA,TXC) == 0);	//wait until data is transmitted
	SET_BIT(UCSRA,TXC);
}

u16 UART_u8ReceiveChar(void){
	while(GET_BIT(UCSRA,RXC)==0);
	//SET_BIT(UCSRA,RXC);
	return UDR;
}

void UART_voidSendString(u8* str){
	u8 i = 0;
	do{	
		UART_voidSendChar(str[i]);
		i++;
	}while(str[i] != '\0');
	
}

void UART_voidSendNumber(u32 Num);

void UART_voidReceiveString(u8* str){
	
	u8 i = 0;
	while(1){
		str[i] = UART_u16ReceiveChar();
		if(str[i]=='\0'){
			break;
		}
		i++;
	}
	str[++i] = '\0';
}