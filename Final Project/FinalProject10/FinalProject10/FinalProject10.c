/*
 * FinalProject10.c
 *
 * Created: 11/22/2022 3:45:23 PM
 *  Author: Kelompok 10
 *	Bagus Hatmoko
 *	Sherly Indiana
 *	Abdan Subekti
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void LCD_Command(char gantiBaris)
{
	PORTB = gantiBaris;
	PORTC &= ~(1<<PORTC0);	/* PORTC0=0 command reg. */
	PORTC &= ~(1<<PORTC1);	/* PORTC1=0 Write operation */
	PORTC |= (1<<PORTC2);	/* Enable pulse */
	_delay_us(1);
	PORTC &= ~(1<<PORTC2);
	_delay_ms(3);
}

void LCD_Char (char gantiKolom)	/* LCD data write function */
{
	PORTB = gantiKolom;
	PORTC |= (1<<PORTC0);	/* PORTC0=1 Data reg. */
	PORTC &= ~(1<<PORTC1);	/* PORTC1=0 write operation */
	PORTC |= (1<<PORTC2);	/* Enable Pulse */
	_delay_us(1);
	PORTC &= ~(1<<PORTC2);
	_delay_ms(1);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	DDRC = 0xFF;		/* Make LCD command port direction as o/p */
	DDRB = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (1 << PORTB5 | 1 << PORTB4 | 1 << PORTB3);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (1 << PORTB3 | 1 << PORTB2);		/* Display ON Cursor OFF */
	LCD_Command (1 << PORTB2 | 1 << PORTB1);		/* Auto Increment cursor */
	LCD_Command (1 << PORTB0);		/* Clear display */
	LCD_Command (1 << PORTB7);		/* Cursor at home position */
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char baris, char kolom, char *str)/* Send string to LCD with xy position */
{
	if (baris == 0 && kolom<16)
	LCD_Command((kolom & 0x0F)|0x80);	/* Command of first baris and required position<16 */
	else if (baris == 1 && kolom<16)
	LCD_Command((kolom & 0x0F)|0xC0);	/* Command of first baris and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}

int main()
{

	LCD_Init();			/* Initialize LCD */

	LCD_String("Kelompok 10");	/* write string on 1st line of LCD*/
	LCD_Command (1 << PORTB7|1 << PORTB6);		/* Go to 2nd line*/
	LCD_String("Mikrokontroller");	/* Write string on 2nd line*/

	return 0;
}