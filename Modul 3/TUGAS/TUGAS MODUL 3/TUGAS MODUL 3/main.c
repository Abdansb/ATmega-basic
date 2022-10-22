/*
 * TUGAS MODUL 3.c
 * Created: 15/09/2022 23.29.09
 * Author : Kelompok 1
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

double duty = 50; // Deklarasi variabel duty tipe double

int main(void)
{
	DDRB = (1 << PORTB3); // PORT B3 sebagai output
	TCCR0 = (1 << WGM00)|(1 << COM01); // Mode phase correct
	TIMSK = (1 << OCIE0); // Interrupt aktif
	
	//OCR0 = (duty/100)*255; // Menghitung nilai OCR
	
	sei(); // Global interrupt
	
	TCCR0 |= (1 << CS02)|(1 << CS00); // Prescaler 1024
	
    while (1) 
    {
		_delay_ms(2000); // Tunda 2 detik
		duty++; // Increment 1
		if (duty > 100)
		{
			duty = 50;
		}
    }
}

ISR(TIMER0_COMP_vect) // Interrupt servis rutin timer 0
{
	OCR0 = (duty/100)*255; // Menghitung nilai OCR
}

