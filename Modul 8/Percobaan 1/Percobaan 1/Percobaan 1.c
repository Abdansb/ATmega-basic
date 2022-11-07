/*
 * ADC input diferensial.c
 *
 * Created: 21/09/2022 04:40:43
 * Author : DELL E7440
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void ADC_INIT()
{
	ADCSRA|=(1<<7);//Enable ADC
	//Set Prescaller
	ADCSRA|=(1<<2)|(1<<1)|(1<<0);//Prescaller 128
	//Set mode operasi ADC
	ADCSRA|=(1<<5);//Aktifkan Auto Trigger
	SFIOR&=~(1<<7)&~(1<<6)&~(1<<5);//Mode free running (ADTS2,ADTS1,ADTS0) diset= 0.
	ADMUX&=~(1<<7)&~(1<<6);//Set tegangan refrensi eksternal 5V pada pin AREF
	ADMUX|=(1<<3)|(1<<0);//aktifkan input diferensial +ADC1, -ADC0 dengan penguatan 10x
	ADMUX&=~(1<<5);//ADLAR = 0
}

int main(void)
{

	ADC_INIT();
	ADCSRA|=(1<<6);//Mulai konversi
	DDRD=0xff;//Set PORTD Sebagai Output
	DDRC=0xff;//Set PORTC Sebagai Output

	while(1)
	{
		_delay_ms(1000);
		if(ADCSRA&(1<<4))//Periksa apakah konversi selesai?
		{
			PORTD=ADCL;//Tampilkan ADCL pada PORTD
			PORTC=ADCH;//Tampilkan ADCH pada PORTC
			ADCSRA|=(1<<4);//Reset ADIF.
		}
	}
}


