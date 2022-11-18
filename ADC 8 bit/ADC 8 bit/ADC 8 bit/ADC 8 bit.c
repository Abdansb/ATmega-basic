/*
 * ADC 8 BIT.cpp
 *
 * Created: 04/11/2022 21:20:49
 * Author : Asus
 */ 

#define F_CPU 16000000L
#include <avr/io.h>

unsigned int ADC_read (unsigned char chnl)
{
	chnl= chnl & 0b00000111;
	ADMUX = 0X40; //Channel A0
	ADCSRA |= (1<<ADSC);
	//ADCSRA |= (1<<ADEN);
	//ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	//ADCSRA |= (1<<ADATE);
	
	//SFIOR &=~(1<<ADTS2)&~(1<<ADTS1)&~(1<<ADTS0);
	//ADMUX |= (1<<REFS1)|(1<<REFS0);
	//ADMUX &=~(1<<ADLAR);
	
	/*----------------------------------*/
	ADCSRA|=(1<<ADIF);
	while(ADCSRA&(1<<ADIF));
	/*----------------------------------*/
	
	return(ADC);
	
}

int main(void)
{
	DDRC=0XFF;
	//DDRA=0X00;
	//PORTA=0XFF;
	ADMUX |= (1<<REFS1)|(1<<REFS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	
	int i = 0;
    while (1) 
    {
			i = ADC_read(0);
			PORTC = i;
    }
}

