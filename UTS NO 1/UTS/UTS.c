/*
 * NO 1.c
 * Created: 22/10/2022 03.49.32
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#define tombol_on bit_is_clear(PINA, PORTA6) // Special Function Register (io reg)
// bit_is_clear(sfr, bit) 
unsigned char i;

int main(void)
{
	DDRB |= (1<<PORTB4);	// PB4 sebagai output LED
	PORTA |= (1<<PORTA6);	// PA6 sebagai input dgn pull-up internal
	 _delay_us(1);	// Tunda sebelum baca balik kondisi pin
	i = PINA; // Baca port pin A
	
    while (1) 
    {
		if(tombol_on) // Jika bit sfr register A clear
		{
			PORTB |= (1<<PORTB4); // Set PB4 HIGH
		} else {
			// Set PB4 LOW & PB 0,1,2,3,5,6,7 sbg input
			PORTB &= ~(1<<PORTB4); 
		}
    }
	_delay_ms(100);
}
