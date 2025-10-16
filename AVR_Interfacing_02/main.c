/*
 * main.c
 *
 *  Created on: Oct 13, 2025
 *      Author: repair
 */

#include <avr/io.h>
#include <avr/delay.h>

#define SET_BIT(Reg,Bitnum)			(Reg |=  (1<<Bitnum) )
#define CLR_BIT(Reg,Bitnum)			(Reg &= ~(1<<Bitnum) )
#define TOGGLE_BIT(Reg,Bitnum)		(Reg ^=  (1<<Bitnum) )
#define GET_BIT(Reg,Bitnum)			(  (Reg>>Bitnum) & 1 )

unsigned char MDIO_u8ConvertToSevenSegment(unsigned char number)
{
	switch(number)
	{
	case 0 : return ~0b00111111; break ;		// 0
	case 1 : return ~0b00000110; break ;		// 1
	case 2 : return ~0b01011011; break ;		// 2
	case 3 : return ~0b01001111; break ;		// 3
	case 4 : return ~0b01100110; break ; 		// 4
	case 5 : return ~0b01101101; break ;		// 5
	case 6 : return ~0b01111101; break ;		// 6
	case 7 : return ~0b00000111; break ;		// 7
	case 8 : return ~0b01111111; break ;		// 8
	case 9 : return ~0b01101111; break ;		// 9

	}
}

void Write7SNumber(unsigned char num , int dly)
{
	int cnt = dly/10 ;
	for(int i=0;i<cnt;i++)
	{
		CLR_BIT(PORTB,1);
		SET_BIT(PORTB,0);
		PORTA = MDIO_u8ConvertToSevenSegment(num%10);
		_delay_ms(5);
		SET_BIT(PORTB,1);
		CLR_BIT(PORTB,0);
		PORTA = MDIO_u8ConvertToSevenSegment(num/10);
		_delay_ms(5);
	}

}

void main(void)
{
	// Connect two 7 Segments to port A
	DDRA = 0xff;

	// Connect two buttons to portc to Count UP/DOWN
	CLR_BIT(DDRC,0);
	CLR_BIT(DDRC,1);
	// pull up resisitor
	SET_BIT(PORTC,0);
	SET_BIT(PORTC,1);

	// Connect the first 7 Segments common pin to Port B Pin 0
	SET_BIT(DDRB,0);
	// Connect the Second 7 Segments common pin to Port B Pin 1
	SET_BIT(DDRB,1);

	SET_BIT(PORTB,0);

	unsigned char up = 0 , down = 0 , count = 0;


	while(1)
	{
		if(GET_BIT(PINC,0)==0)
		{
			// debounce
			_delay_ms(5);
			if(GET_BIT(PINC,0)==0)
			{
				count++ ;
			}

			while(GET_BIT(PINC,0)==0);

		}
		if(GET_BIT(PINC,1)==0)
		{
			// debounce
			_delay_ms(5);
			if(GET_BIT(PINC,1)==0)
			{
				if(count==0)
					count = 99 ;
				else
					count-- ;
			}

			while(GET_BIT(PINC,1)==0);
		}

		if(count==100)	count = 0 ;

		Write7SNumber(count , 10);


	}
}

