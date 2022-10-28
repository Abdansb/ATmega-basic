/*
 * _1.c
 *
 * Created: 28/10/2022 00.56.32
 *  Author: Lenovo
 */ 


#define F_CPU 16000000L
#include <avr/io.h>

void ADC_INIT()
{
	ADCSRA |= (1 << 7); // ADC enable ADEN bit 7
	ADCSRA |= (1 <<2)|(1 << 1)|(1 << 0); // ADPS prescaler select bits
	ADCSRA &=~ (1 << 5); //Aktifkan auto trigger
	SFIOR &= ~(1 << 7) &~ (1 << 6) &~ (1 << 5); // mode free running, bit 765 isinya 0
	
	ADMUX |= (1 << 7)|(1 << 6); // set refernsi internal 2.56 V
	ADMUX |= (1 << 0); // Analaog channel & gain selection bit channel 1
	ADMUX &= ~(1 << 5); // Right adjusted presentation adc result
}


int main(void)
{
	ADC_INIT();
	DDRD = 0xff;
	DDRC = 0xff;
	DDRB = 0x00;
	PORTB = 0xFF;

	while (1)
	{
		if (~PINB&(1<<0)) ADCSRA|=(1<<6); // 
		if(ADCSRA&(1<<4))
		{
			PORTD = ADCL;
			PORTC = ADCH;
			ADCSRA |= (1 << 4);
		}
	}
}

