/*
 * analog comparator-tugas.c
 * Created: 30/09/2022 07.17.27
 * Author : abdan
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void analog_comparator_INIT()
{
	ACSR &=~ (1 << 7);
	ACSR |= (1 << 6);
}
int main(void)
{
    DDRB &=~ (1 << 3);
	PORTB &=~ (1 << 3);
	DDRD |= (1 << 2)|(1 << 3)|(1<<4)|(1<<5);
	PORTD &=~ (1 << 2) &~ (1 << 3)&~ (1 << 4)&~ (1 << 5);
	analog_comparator_INIT();
    while (1) 
    {
		if (ACSR & (1 << 5))
		{
			PORTD |= (1 << 2)|(1 << 4);
			PORTD &=~ (1 << 3)&~(1<<5);
			_delay_loop_2(65535);
		} 
		else
		{
			PORTD &=~ (1 << 2)&~(1<<4);
			PORTD |= (1 << 3)|(1 << 5);
			_delay_loop_2(65535);
		}
    }
}
