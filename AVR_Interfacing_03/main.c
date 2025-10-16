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


unsigned char rKeyPad[4][4] = { {'7','8','9','U' },
								{'4','5','6','D' },
								{'1','2','3','H' },
								{'S','0','R','T' } };

unsigned char MDIO_u8ConvertToSevenSegment(unsigned char number)
{
	switch(number)
	{
	case '0' : return ~0b00111111; break ;		// 0
	case '1' : return ~0b00000110; break ;		// 1
	case '2' : return ~0b01011011; break ;		// 2
	case '3' : return ~0b01001111; break ;		// 3
	case '4' : return ~0b01100110; break ; 		// 4
	case '5' : return ~0b01101101; break ;		// 5
	case '6' : return ~0b01111101; break ;		// 6
	case '7' : return ~0b00000111; break ;		// 7
	case '8' : return ~0b01111111; break ;		// 8
	case '9' : return ~0b01101111; break ;		// 9
	default  : return ~0b01000000; break ;		// -

	}
}


void main(void)
{

	DDRA  = 0xff;
	PORTA = 0xff;

	DDRC  = 0x0f;
	PORTC = 0xff;	//pull-up last 4 pins and output high first 4 pins


	// Connect the first 7 Segments common pin to Port B Pin 0
	SET_BIT(DDRB,0);
	// Connect the Second 7 Segments common pin to Port B Pin 1
	SET_BIT(DDRB,1);

	int r_index=-1 , c_index=-1  ;

	while(1)
	{

			for(int i=0 ; i<4;i++)
			{
				CLR_BIT(PORTC,i);
				for(int j=4;j<8;j++)
				{
					// check if button is pressed
					if(GET_BIT(PINC,j)==0)
					{
						_delay_ms(5);
						if(GET_BIT(PINC,j)==0)
						{
							r_index = i;
							c_index = j;
							break ;
						}
					}

				}
				SET_BIT(PORTC,i);
			}

				PORTA = MDIO_u8ConvertToSevenSegment(rKeyPad[r_index][c_index-4] );
		}

}





