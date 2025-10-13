/*
 * main.c
 *
 *  Created on: Oct 13, 2025
 *      Author: repair
 */

#include <avr/io.h>
#include <avr/delay.h>


void main(void)
{
	DDRA  = 0b11111111;


	while(1)
	{
		for(int i=0;i<8;i++)
		{
			PORTA = 1<<i ;
			_delay_ms(300);
		}
	}
}

