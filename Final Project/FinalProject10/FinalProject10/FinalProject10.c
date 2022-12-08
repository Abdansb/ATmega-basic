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
char gprmc[]={'$','G','P','G','G','A'};	// String untuk dicocokan ke data gps
/****************Array GPS***************/
char latitude[12];						
char logitude[12];
char time[12];
int jam;

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
		if(buf[ind-1] != gprmc[ind-1])      // Baris yg tidak ada "$GPRMC" akan diabaikan
		ind=0;
	}
	if(ind>=50)								// Jika "$GPRMC" ketemu, copy semuanya ke variabel buf[100]
	
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

int main()
{
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
		if(stringReceived == 1)
		{
			// Hentikan interrupt dengan clear SREG, interrupt global disable
			cli();
			
			for(int i=0;i<ind;i++)						// copy satu baris dari GPRMC
			ind=0;										// setelahnya index nol lagi
			
			stringReceived=0;							// baris sudah diterima, flag nol lagi
			
			LCD_Command (1 << PORTA7);					// Posisi kursor LCD kolom & baris pertama
			LCD_String("LAT: ");
			
			// Pilih string dari GPRMC yang memuat latitude, ada di buf[17] sampai buf[29]
			for(int i=18;i<30;i++)
			{
				latitude[i]=buf[i];						// Copy time ke array sendiri
				LCD_Char(latitude[i]);					// Panggil fungsi tampilkan di LCD
			
			}
			
			LCD_Command (1 << PORTC7|1 << PORTC6);		// Pindah baris kedua LCD
			LCD_String("LOG:");
			
			// Pilih string dari GPRMC yang memuat latitude, ada di buf[30] sampai buf[43]
			for(int i=30;i<43;i++)
			{
				logitude[i]=buf[i];						// Copy logitude ke array sendiri
				LCD_Char(logitude[i]);					// Panggil fungsi tampilkan di LCD
				if(i==38)
				{
					//LCD_Char(' ');
					i++;
				}
			}

			sei(); // Ketika data gps dari interrupt sudah ditampilkan maka interrupt jalan lagi
			_delay_ms(3000);
			LCD_Clear();
			LCD_String("Time: ");
			for(int i=7;i<29;i++)
			{
				time[i]=buf[i];
				LCD_Char(time[i]);
			}



			_delay_ms(3000); // Tunda 10 detik sebelum scan data gps baru lagi
			
			
		}
	}

	return 0;
}