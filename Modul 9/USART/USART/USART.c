/*
 * USART.c
 * Created: 10/11/2022 22.26.36
 * Author: Abdansb
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define BRC ((F_CPU/16/BAUD)-1)

void USART_INIT(unsigned int UBRR_baud)
{
	UBRRH = (unsigned char)(((F_CPU/16/UBRR_baud)-1)>>8);
	UBRRL = (unsigned char)((F_CPU/16/UBRR_baud)-1);
	UCSRC = (1 << URSEL)|(0 << UMSEL)|(0 << UPM1)|(0 << UPM0)|
			(0 << USBS)|(1 << UCSZ1)|(1 << UCSZ0)|(0 << UCPOL);
	UCSRB &=~ (1 << 2);
	UCSRB |= (1 << 4)|(1 << 3);
	UCSRA &=~ (1 << 1) &~ (1 << 0);
}

void delay_ms (int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

static int uart_getchar(FILE * stream)
{
	loop_until_bit_is_set(UCSRA, 7);
	return UDR;
}

static FILE mystdout_mystdin = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);


int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}