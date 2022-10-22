/*
 * NO 1.c
 * Created: 22/10/2022 03.49.32
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#define _NOP()  asm("nop")
#include <avr/io.h>
unsigned char i;
int main(void)
{
	PORTB = (1<<PB7)|(1<<PB6)|(1<<PB1)|(1<<PB0);
	DDRB = (1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
  _NOP();
  i = PINB;
    while (1) 
    {
    }
}

