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



void main(void)
{
	unsigned char pinValue_0 ;
	unsigned char pinValue_1 ;
	unsigned char pinValue_2 ;

	// set port direction output
	DDRA  = 0b11111111;


	DDRB  = 0b00000001;
	PORTB = 0b00000001;

	//set portC0 direction input
	//CLR_BIT(DDRC,0);
	DDRC  = 0b00000000;

	// activate pull-up Resistor on pin0
	//SET_BIT(PORTC,0);
	PORTC = 0b00000111;

	//
	unsigned char index = 0;
	SET_BIT(PORTA,index);



//	SET_BIT(PORTB,0);


	while(1)
	{
		pinValue_0 = GET_BIT(PINC,0);
		pinValue_1 = GET_BIT(PINC,1);
		pinValue_2 = GET_BIT(PINC,2);

		if(GET_BIT(PINC,0) == 0)
		{
			_delay_ms(10);
			if(GET_BIT(PINC,0) == 0)
			{
				CLR_BIT(PORTA, index);
				if(index == 0 )	index = 7 ;
				else 			index--	  ;
				SET_BIT(PORTA, index);


				while(GET_BIT(PINC,0)==0);
			}

		}

		if(GET_BIT(PINC,1) == 0)
		{
			_delay_ms(10);
			if(GET_BIT(PINC,1) == 0)
			{

				TOGGLE_BIT(PORTA, index);

				while(GET_BIT(PINC,1)==0);
			}
		}

		if(GET_BIT(PINC,2) == 0)
		{
			_delay_ms(10);
			if(GET_BIT(PINC,2) == 0)
			{
				CLR_BIT(PORTA, index);
				if(index == 7 )	index = 0 ;
				else			index++	  ;
				SET_BIT(PORTA, index);

				while(GET_BIT(PINC,2)==0);
			}
		}

	}

}




