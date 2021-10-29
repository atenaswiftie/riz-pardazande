#ifndef F_CPU

#define F_CPU 4000000UL


#include <stdio.h>

#include <avr/io.h>    

#include <util/delay.h>  



#define a1 (1<<PD4)

#define a2 (1<<PD5)

#define a3 (1<<PD6)

#define a4  (1<<PD7)

#define SW (1<<PD3)


int main(void){

	DDRD |= a1 | a2 | a3| a4;

	DDRD &= ~SW;

	PORTD |= SW;



	while(1){



		if(!(PIND & SW)){


		PORTD |= a1;

		PORTD &= ~a2;

		PORTD &= ~a3;

		PORTD |= a4;

		_delay_ms(100);


		PORTD |= a1;

		PORTD &= ~a2;

		PORTD |= a3;

		PORTD &= ~a4;

		_delay_ms(100);

		PORTD &= ~a1;

		PORTD |= a2;

		PORTD |= a3;

		PORTD &= ~a4;

		_delay_ms(100);

		PORTD &= ~a1;

		PORTD |= a2;

		PORTD &= ~a3;

		PORTD |= a4;

		_delay_ms(100);

		}

	else{

		PORTD &= ~a1;

		PORTD |= a2;

		PORTD &= ~a3;

		PORTD |= a4;

		_delay_ms(100);
		PORTD &= ~a1;

		PORTD |= a2;

		PORTD |= a3;

		PORTD &= ~a4;

		_delay_ms(100);

		PORTD |= a1;

		PORTD &= ~a2;

		PORTD |= a3;

		PORTD &= ~a4;

		_delay_ms(100);

		PORTD |= a1;

		PORTD &= ~a2;

		PORTD &= ~a3;

		PORTD |= a4;

		_delay_ms(100);
			}

	}

return(0);

}