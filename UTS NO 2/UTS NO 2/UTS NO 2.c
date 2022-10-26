/*
 * UTS_NO_2.c
 * Created: 26/10/2022 04.07.59
 *  Author: Abdan Subekti
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#define RES 500

void adc_init()
{
	// Tegangan referensi AREF=AVCC kapasitor eksternal
	ADMUX = (1<<REFS0);
	// ADC enable ADEN bit 7
	ADCSRA |= (1 << 7); 
	// ADPS prescaler 128, 16000000/128 = 125000
	ADCSRA |= (1 <<2)|(1 << 1)|(1 << 0); 
	// Mode free running, bit 7,6,5 = 0
	SFIOR &= ~(1 << 7) &~ (1 << 6) &~ (1 << 5); 
	
}

// Fungsi baca ADC
uint16_t adc_read(uint8_t ch)
{
	ch &= 0b00000111; 
	ADMUX = (ADMUX & 0xF8)|ch;   
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}

int main()
{
	uint16_t adc_result0, adc_result1;
	char int_buffer[10];
	DDRC = 0x01;
	

	adc_init();
	

	
	_delay_ms(50);
	
	while(1)
	{
		adc_result0 = adc_read(0);     

		if (adc_result0 < RES)
		PORTC = 0x01;
		else
		PORTC = 0x00;
		
		
	}
}