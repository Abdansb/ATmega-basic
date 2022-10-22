/*
 * 16bit pwm.c
 *
 * Created: 21/09/2022 11.26.50
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

double duty = 50;

int main(void){

	DDRD = (1 << PORTD4); // PORT D4 sebagai output
	
	// PWM, phase correct, clear OC on compare, pembagian pengaturan wgm, com, cs A & B sendiri sendiri
	TCCR1A |= (1 << COM1B1) | (1<<WGM11) | (1 << WGM10);	
	
	//Set OC on compare, no prescaler alias x1
	TCCR1B |= ( 1<<WGM13 )|  (1<<CS10);		
	
	// interrupt enable
	TIMSK = (1 << OCIE1A); 
	sei();
	
	

	
	while(1){
		/*_delay_ms(2000);
		duty++;
		
		if(duty>100)
		{
			duty=50;
		}*/

	}
	
}

ISR(TIMER1_COMPA_vect) // Interrupt servis rutin timer 1
{
		
		OCR1A = 65535;
		OCR1B = (duty/100)*OCR1A;
}

