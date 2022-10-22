/*
 * Percobaan Analog Komparator.c
 * Created: 30/09/2022 04.56.38
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void analog_comparator_INIT()
{
	ACSR &=~ (1 << 7); // KOMPARATOR ANALOG AKTIF
	// Input terhubung ke non invert komparator (AIN0) Vref internal 1,22 V
	
	ACSR |= (1 << 6); // Set band gap (datasheet)
}

int main(void)
{
    DDRB =~ (1 << 3); //PB3 (AIN1) SEBAGAI INPUT
	PORTB &=~ (1 << 3); //NONAKTIFKAN PULL UP RES
	DDRD |= (1 << 2)|(1 << 3); //PD2 & PD3 SEBAGAI OUTPUT
	PORTD &=~ (1 << 2) &~ (1 <<3); // SET INITIAL VALUE PD2 PD3 == 0
	analog_comparator_INIT();
	
    while (1) 
    {
		if (ACSR & (1 << 5))
		{
			PORTD |= (1 << 2); // CEK TEGANGAN APAKAH PB3 (AIN0) < 1,22 V
			PORTD &=~ (1 <<3);
			_delay_loop_2(65536);
		} 
		else
		{
			PORTD &=~ (1 << 2);
			PORTD |= (1 <<3);
			_delay_loop_2(65536); // CEK TEGANGAN APAKAH PB3 (AIN0) > 1,22 V
		}
    }
}

