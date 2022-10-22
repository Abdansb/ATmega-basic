/*
 * Tugas Modul 1.c
 * Created: 02/09/2022 21.38.53
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define tombol PD3 
#define tombol_on bit_is_clear(PIND, tombol)

int main(void)
{
    DDRB |= (1 << PORTB3); // Port B3 sebagai output 
	PORTD |= (1 << tombol); // Port D sebagai input
		
    while (1) 
    {
		if (tombol_on)
		{
			PORTB |= (1 << PORTB3);
		} else {
			PORTB &= ~(1 << PORTB3); 
		}
    }
	_delay_ms(100);
}

