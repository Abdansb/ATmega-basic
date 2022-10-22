/*
 * Tugas Modul 2.c
 *
 * Created: 21/09/2022 07.27.42
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
// Variabel led dan increment
int loop;
char led;

int main(void)
{
    DDRB = (1 << DDB0)+(1 << DDB1)+(1 << DDB2)+(1 << DDB3);
	TCCR0 = (1 << WGM01);
	OCR0 = 200;
	led = 0x01;
	TIMSK = (1 << OCIE0);
	sei();
	TCCR0 |= (1 << CS00)|(1 << CS02);
	
    while (1) 
    {
    }
}
ISR(TIMER0_COMP_vect)
{
	loop++;
	if (loop < 4)
	{
		PORTB = led;
		led = led << 1;
	} if (loop > 3)
	{
		PORTB = 0x00;
		led = 0x01;
		loop = 0;
	}
}
