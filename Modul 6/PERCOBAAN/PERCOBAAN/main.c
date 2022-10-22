/*
 * PERCOBAAN.c
 * ADC CONVERTER (free running)
 * Created: 07/10/2022 04.43.52
 * Author : Kelompok 1
 */ 
#define F_CPU 16000000L
#include <avr/io.h>

void ADC_INIT()
{
	ADCSRA |= (1 << 7); // ADC enable ADEN bit 7
	ADCSRA |= (1 <<2)|(1 << 1)|(1 << 0); // ADPS prescaler select bits
	SFIOR &= ~(1 << 7) &~ (1 << 6) &~ (1 << 5); // mode free running, bit 765 isinya 0
	
	ADMUX |= (1 << 7)|(1 << 6); // set refernsi internal 2.56 V
	ADMUX |= (1 << 0); // Analaog channel & gain selection bit (MUX0)
	// single ended input adc 0
	ADMUX &= ~(1 << 5); // Right adjusted presentation adc result
}


int main(void)
{
	ADC_INIT();
	ADCSRA |= (1 << 6); // ADSC adc start conversion
	// free running 25 adc clock cycles
	DDRD = 0xff;
	DDRC = 0xff;

    while (1) 
    {
		if (ADCSRA & (1 << 4)) // ADIF interrupt flag, jika adc selesai
		{
			PORTD = ADCL;
			PORTC = ADCH;
			ADCSRA |= (1 << 4);
		}
    }
}

