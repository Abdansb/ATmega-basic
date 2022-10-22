/*
 * Timer dan Counter.c
 * Created: 09/09/2022 14.56.23
 * Author : Abdan Subekti (Kelompok 1)
 */ 

#define  F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>

int ulang;

int main(void)
{
    DDRB = (1 << DDB0);
	TCCR0 = (1 << WGM01);
	OCR0 = 200;
	TIMSK = (1 << OCIE0);
	sei();
	TCCR0 |= (1 << CS00)|(1 << CS02);
    while (1) 
    {
    }
}

ISR(TIMER0_COMP_vect)
{
	ulang++;
	if (ulang > 80);
	{
		PORTB ^= (1 << PORTB0);
		ulang = 0;
	}
}
	