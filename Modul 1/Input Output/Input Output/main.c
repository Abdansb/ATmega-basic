/*
 * Input Output.c
 * Created: 02/09/2022 19.18.06
 * Author : Abdan Subekti
 */ 
#define F_CPU 16000000L
#include <avr/io.h>

int main(void)
{
	DDRC |= (1 << 3);
    while (1) 
    {
		PORTC = (1 << 3);
    }
}

