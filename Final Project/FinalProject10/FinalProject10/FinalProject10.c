/*
 * FinalProject10.c
 *
 * Created: 11/22/2022 3:45:23 PM
 *  Author: Abdan Subekti
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_Data_Dir DDRC		// DDR Data Port LCD
#define LCD_Command_Dir DDRA	// DDR Command Port LCD
#define LCD_Data_Port PORTC		// Sinyal data LCD port C
#define LCD_Command_Port PORTA	// Command LCD port A
#define RS PA5					// LCD Register select pin
#define RW PA6					// LCD Read / Write pin
#define EN PA7					// LCD enable pin (pulse)

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) // BAUD_PRESCALE = 103
/******* UBRR = F_CPU / (BAUD x 16 unsigned long) - 1 **********/

char buf[100];							// Variabel sementara data gps
volatile char ind,flag,stringReceived;	// Variabel update data
char gpgga[]={'$','G','P','G','G','A'};	// String untuk dicocokan ke data gps
/****************Array GPS***************/
char latitude[12];						
char logitude[12];
char altitude[12];
char time[12];

void serialbegin()
{	
	// Pilih register UCSRC & Frame format 8 data bits
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); 
	
	UBRRH = (BAUD_PRESCALE >> 8);			// Load upper 8-bits
	UBRRL = BAUD_PRESCALE;					// Load lower 8-bits of the baud rate
	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);	// Aktifkan Rx, Tx, dan interrupt flag Rx
}

ISR(USART_RXC_vect)							// Interrrupt aktif ketika USART Receive Complete
{
	char ch=UDR;							// Tampung USART Data ke variable ch
	buf[ind]=ch;							// copy data ch ke array buf[]
	ind++;									// increment index buf untuk scan data dari gps
	if(ind<7)								// scan data 6 karakter pertama tiap baris
	{
		if(buf[ind-1] != gpgga[ind-1])      // Baris yg tidak ada "$GPGGA" akan diabaikan
		ind=0;
	}
	if(ind>=50)								// Jika "$GPGGA" ketemu, copy semuanya ke variabel buf[100]
	
	// set flag ke variabel ketika baris diatas diterima seluruhnya
	stringReceived=1;						
}

void LCD_Command(unsigned char gantiBaris)
{
	LCD_Data_Port= gantiBaris;		/* Parameter gantiBaris PORTC 6 & 7 = 1 */
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Aktifkan LCD dengan pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);	/* Matikan pulse */
	_delay_ms(3);
}

void LCD_Char (unsigned char char_data)	/* Fungsi print LCD */
{
	LCD_Data_Port= char_data;		/* Parameter untuk print tiap karakter */
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Aktifkan LCD dengan pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);	/* Matikan pulse */
	_delay_ms(1);
}

void LCD_Init (void)			/* Inisialisasi LCD */
{
	LCD_Command_Dir = 0xFF;		/* set LCD command port sebagai output */
	LCD_Data_Dir = 0xFF;		/* set LCD data port sebagai output */
	_delay_ms(20);				/* Delay untuk menunggu inisialisasi LCD >15 ms */
	
	LCD_Command (1 << PORTA5 | 1 << PORTA4 | 1 << PORTA3);		/* mode LCD dalam mode 8-bit (pin) */
	LCD_Command (1 << PORTA3 | 1 << PORTA2);					/* Display on & cursor off */
	LCD_Command (1 << PORTA2 | 1 << PORTA1);					/* Auto Increment cursor */
	LCD_Command (1 << PORTA0);									/* Clear LCD */
	LCD_Command (1 << PORTA7);									/* Posisi kursor pada kolom pertama */
}

void LCD_String (char *str)		/* Pecah string ke char satu-satu ke tampilan LCD */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Kirim string ke fungsi LCD_char untuk ditampilkan */
	{
		LCD_Char (str[i]);
	}
}

void LCD_Clear()
{
	LCD_Command (1 << PORTC0);		/* clear display */
	LCD_Command (1 << PORTC7);		/* cursor di kolom & baris pertama */
}

void ADC_INIT()
{
	ADCSRA |= (1 << 7); // ADC enable ADEN bit 7
	ADCSRA |= (1 <<2)|(1 << 1)|(1 << 0); // ADPS prescaler select bits
	SFIOR &= ~(1 << 7) &~ (1 << 6) &~ (1 << 5); // mode free running, bit 765 isinya 0
	
	ADMUX |= (1 << 6); // set refernsi avcc
	ADMUX |= (1 << 4)|(1 << 3)|(1 << 2)|(1 << 1);


	ADCSRA |= (1 << 6);
	DDRB = 0xff;
}

void Tombol_Init()
{
	DDRD = 0x00;
	PORTD |= (1 << PORTD2);
	// Aktifkan interupsi eksternal INT0 (PD2)
	GICR = (1 << INT0);
	// Kontrol trigger interupsi eksternal (aktif sisi naik)
	MCUCR = (1 << ISC00)|(1 << ISC01);
	// Status register, mengaktifkan interupsi global (set bit i)
}

// Rutin interupsi sumber/vector INT0
ISR(INT0_vect)
{
	LCD_String("Abdan");
	_delay_ms(5000);
}

int main()
{
	float Vcc_value = 0 /* measured Vcc value */;
	uint16_t ADC_RES_L = 0;
	uint16_t ADC_RES_H = 0;
	char *Value[50];
	
	ADC_INIT();
	//Tombol_Init();
	LCD_Init();								// Inisialisasi LCD
	serialbegin();							// Inisialisasi usart

	LCD_String("Kelompok 4");
	LCD_Command (1 << PORTC7|1 << PORTC6);	// Pindah baris kedua
	LCD_String("Mikrokontroller");
	_delay_ms(3000);
	LCD_Clear();
	
	/* Mulai interrupt usart, set SREG bit ke-8 = 1, interrupt global enable */
	sei();
	
	
	
	while(1)
	{
		if (ADCSRA & (0x01 << ADIF)) /* check if ADC conversion complete */
		{
			ADC_RES_L = (int)ADCL;
			ADC_RES_H = (int)ADCH*256;
			Vcc_value = (1024*1.22)/(ADC_RES_L+ADC_RES_H);
			sprintf(Value,"Battery : %.2f V",Vcc_value);
			ADCSRA |= (1 << 4);
		}
		LCD_Clear();
		LCD_String(Value);
		_delay_ms(3000);

		if(stringReceived == 1)
		{
			// Hentikan interrupt dengan clear SREG, interrupt global disable
			cli();
			
			for(int i=0;i<ind;i++)						// copy satu baris dari GPGGA
			ind=0;										// setelahnya index nol lagi
			
			stringReceived=0;							// baris sudah diterima, flag nol lagi
			
			LCD_Command (1 << PORTA7);					// Posisi kursor LCD kolom & baris pertama
			LCD_String("LAT: ");
			
			// Pilih string dari GPGGA yang memuat latitude, ada di buf[17] sampai buf[29]
			for(int i=18;i<30;i++)
			{
				latitude[i]=buf[i];						// Copy time ke array sendiri
				LCD_Char(latitude[i]);					// Panggil fungsi tampilkan di LCD
				
			}
			
			LCD_Command (1 << PORTC7|1 << PORTC6);		// Pindah baris kedua LCD
			LCD_String("LOG:");
			
			// Pilih string dari GPGGA yang memuat latitude, ada di buf[30] sampai buf[43]
			for(int i=30;i<43;i++)
			{
				logitude[i]=buf[i];						// Copy logitude ke array sendiri
				LCD_Char(logitude[i]);					// Panggil fungsi tampilkan di LCD
				if(i==32)
				{
					//LCD_String(".");
					i++;
				}
			}

			sei(); // Ketika data gps dari interrupt sudah ditampilkan maka interrupt jalan lagi
			_delay_ms(3000);
			LCD_Clear();
			LCD_String("TIME: ");
			for(int i=7;i<16;i++)
			{
				time[i]=buf[i];
				LCD_Char(time[i]);
			}

			LCD_Command (1 << PORTC7|1 << PORTC6);		// Pindah baris kedua LCD
			LCD_String("ALTI: ");
			for(int i=54;i<60;i++)
			{
				altitude[i]=buf[i];
				LCD_Char(altitude[i]);
				if(i==58)
				{
					LCD_String(" MDPL");
					i++;
				}
			}


			_delay_ms(3000); // Tunda 10 detik sebelum scan data gps baru lagi
			
			
		}
	}

	return 0;
}
