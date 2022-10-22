/*
 * Percobaan Praktikum 4.c
 * Program Interrupt Eksternal
 * Created: 23/09/2022 04.28.02
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#define Tombol PORTD2
#define LED PORTB3
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{		
    DDRD = 0x00;						// PD sebagai input
	PORTD = 0x04;						// Nilai awal pin PD2 HIGH
	
	// Aktifkan interupsi eksternal INT0 (PD2)
	GICR = (1 << INT0);
	// Kontrol trigger interupsi eksternal (aktif sisi naik)
	MCUCR = (1 << ISC00)|(1 << ISC01);
	// Status register, mengaktifkan interupsi global (set bit i)
	sei();
	
    while (1) {
		// Fungsi kedip dengan EX-OR
		PORTB ^= (1<<PORTB3);
		_delay_ms(2000);				// Delay kedip 2 detik
	}
}
// Rutin interupsi sumber/vector INT0
ISR(INT0_vect)
{
	// EX-OR kan PB untuk fungsi nyala dan mati LED dengan button
	DDRB^= (1<<PORTB3);					// PB sebagai output HIGH
	_delay_ms(500);

}