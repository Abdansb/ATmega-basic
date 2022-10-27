/*
 * UTS_NO_2.c
 * Created: 26/10/2022 04.07.59
 *  Author: Abdan Subekti
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{	
	// Variabel konversi biner desimal
	int nilaiBawah;
	int nilaiAtas;
	int nilaiSensor;

	DDRD = 0xff;    // PORTD ouput
	PORTD=0x00;		// Pull LOW
	
	ADCSRA |= (1 << 7);						// ADC enable ADEN bit 7
	ADCSRA |= (1 <<2)|(1 << 1)|(1 << 0);	// ADPS prescaler 128, 16000000/128 = 125000
	ADMUX = (1<<REFS0);						// Tegangan referensi AREF=AVCC + kapasitor eksternal

	// Single ended input ADC, Analog channel & gain selection bit (MUX0)
	ADMUX |= (1 << 0); 
	// Mode free running, bit 7,6,5 = 0
	SFIOR &= ~(1 << 7) &~ (1 << 6) &~ (1 << 5);

	while(1)
	{
		ADCSRA |= (1 << 6); // ADSC, ADC start conversion, free running 25 clock

		if (ADCSRA & (1 << 6)) // Tunggu hingga ADC selesai
		{
			nilaiBawah = (int)ADCL;
			nilaiAtas = (int)ADCH*256;
			nilaiSensor = nilaiAtas+nilaiBawah;
		
				if (nilaiSensor>768)
					{	PORTD = 0x01;	}
				else if (nilaiSensor>511)
					{	PORTD = 0x02;	}	
				else if (nilaiSensor>255)
					{	PORTD = 0x04;	}
				else if (nilaiSensor>1)
					{	PORTD = 0x08;	}       
		}      
	}
}