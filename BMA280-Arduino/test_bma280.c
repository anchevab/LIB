/****************************************************************************
Title:    Access 3-Axis Accelerometer BMA280 using I2C interace
Author:   Peter Fleury <pfleury@gmx.ch> http://jump.to/fleury
File:     $Id: test_bma280.c,v 1.2 2003/12/06 17:07:18 peter Exp $
Software: AVR-GCC 3.3
Hardware: Arduino Uno at 16 Mhz

Description:
    This example shows how the I2C library i2cmaster.S can be used to 
    access a 3-Axis BMA280 Accelerometer 

    Based on Atmel Application Note AVR300, adapted to AVR-GCC C interface

*****************************************************************************/
#include <avr/io.h>
#include <string.h>
#include <math.h>

#include "i2cmaster.h"

#define F_CPU 16000000UL
#define BAUD 57600

#include <util/setbaud.h>

#include <util/delay.h>

#define BMA280

#define SLAVE_ADRESSE 0x70

#include <avr/io.h>
#include <avr/interrupt.h>

/*
Wiring:
I2C-Connection with Arduino Uno:
12 SCX = SCL,  Pull-Up (4.7k)  to 3.3V       A5 at Arduino
  2 SDA = SDA, Pull-Up (4.7k)  to 3.3V       A4 at Arduino
1,8,9  			to GND at Arduino
3,7,11 PS    	to 3.3V at Arduino

*/

/*
 if this Symbol is set serial output is done in Package format
 if this symbol is not defined output will be as Print Strings of 3 number values
*/
#define OUTPUT_PACKAGE_FORMAT 1

uint8_t rawADC[6];


/*
	Routines for interrupt Timer:
*/
void timer_init()
{
    // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = 12000;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 64 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    sei();          // enable global interrupts
}

/*
	Interrupt Service Routine for interrupt Timer:
*/
ISR(TIMER1_COMPA_vect)
{
	long x,y,z;
	double roll,ptich,rafv;
	int i,n=16;
	x=y=z=0;
	
	char s[256];
	
	sei();
	for(i=0;i<n;i++)
	{
		read_bma280();
		x += ((rawADC[1]<<8) | (rawADC[0])) >>2;
		y += ((rawADC[3]<<8) | (rawADC[2])) >>2;
		z += ((rawADC[5]<<8) | (rawADC[4])) >>2;;
	}
  
	x /= n;
	y /= n;
	z /= n;
	

//	roll = atan( (double) x / (double) z)  * (double) 180.0 / (double)3.14159;
//	pitch  = atan( (double) y / sqrt( (double)(x*x + z*z))) * (double) 180.0 / (double)3.14159;
//	r = sqrt ((double)x*x+(double)y*y+(double)z*z);
//	ravg = ravg *(1.0 - a) + r * a;
#ifdef OUTPUT_PACKAGE_FORMAT	
	rawADC[1]= x>>8;
	rawADC[0] = x & 0xff;
	rawADC[3]= y>>8;
	rawADC[2] = y & 0xff;
	rawADC[5]= z>>8;
	rawADC[4] = z & 0xff;
	send_packet(rawADC,6);
#else
	sprintf(s,"%ld %ld %ld\n",x,y,z);
    uart_putstring(s);
#endif

	cli();
}


// ************************************************************************************************************
// I2C Accelerometer BMA280
// ************************************************************************************************************
#if defined(BMA280)
#if !defined(BMA280_ADDRESS) 
  #define BMA280_ADDRESS 0x18 // SDO PIN on GND
  //#define BMA280_ADDRESS 0x19  // SDO PIN on Vddio
#endif
// ************************************************************************************************************
// I2C general functions
// ************************************************************************************************************
#define INTERNAL_I2C_PULLUPS


void init_bma280()
{
    i2c_start_wait((BMA280_ADDRESS<<1)+I2C_WRITE);     // set device address and write mode
        i2c_write(0x10);                        // write start address = 0
        i2c_write(0x09);                        // write data to address 0
		i2c_stop();
		_delay_ms(5);
		   i2c_start_wait((BMA280_ADDRESS<<1)+I2C_WRITE);   
        i2c_write(0x0f);                        //    "    "   "    "    1
        i2c_write(0x08);                        //    "    "   "    "    2
        i2c_stop();  
}

void read_bma280()
{
	  i2c_start_wait((BMA280_ADDRESS<<1)+I2C_WRITE);      // set device address and write mode
        i2c_write(0x02);                         // write address = 0
        i2c_rep_start((BMA280_ADDRESS<<1)+I2C_READ);        // set device address and read mode
        rawADC[0] = i2c_readAck();                       // read one byte form address 0
        rawADC[1] = i2c_readAck();                       //  "    "    "    "     "    1
        rawADC[2] = i2c_readAck();                       //  "    "    "    "     "    2
        rawADC[3] = i2c_readAck();                         //  "    "    "    "     "    3
		rawADC[4] = i2c_readAck();                       //  "    "    "    "     "    2
        rawADC[5] = i2c_readNak();      
        i2c_stop();                              // set stop condition = release bus
}

#endif

// ************************************************************************************************************
#if defined(BMA020)
int init_bma020()
{
	uint8_t 	control;
 uart_putstring("init BMA020\n");
	if(!(i2c_start(SLAVE_ADRESSE+I2C_WRITE))) //Slave bereit zum schreiben?
			{
				 uart_putstring("BMA020 ready\n");
				i2c_write(0x15); // Buffer Startadresse setzen 	
				i2c_write(0x80);
				i2c_stop();       // Zugriff beenden
			}
	else
	{
	 uart_putstring("not BMA020 ready\n");
	}
			
			
	i2c_start_wait(SLAVE_ADRESSE+I2C_WRITE); 
			i2c_write(0x14); 
			i2c_write(0x71);
			i2c_rep_start(SLAVE_ADRESSE+I2C_READ); 
			control = i2c_readNak();
			control = control >> 5;  //ensure the value of three fist bits of reg 0x14 see BMA020 documentation page 9
			control = control << 2;
			control = control | 0x00; //Range 2G 00
			control = control << 3;
			control = control | 0x00; //Bandwidth 25 Hz 000
			i2c_start_wait(SLAVE_ADRESSE+I2C_WRITE); 
			i2c_write(0x14); 
			i2c_write(control);
			i2c_stop();
}

void read_bma020()
{

	i2c_start_wait(SLAVE_ADRESSE+I2C_WRITE); 
	i2c_write(0x02); 
	
	i2c_rep_start(SLAVE_ADRESSE+I2C_READ); 
	rawADC[0] = i2c_readAck(); // Bytes lesen...
	rawADC[1]= i2c_readAck(); 
	rawADC[2]= i2c_readAck(); 
	rawADC[3]= i2c_readAck(); 
	rawADC[4]= i2c_readAck(); 
	rawADC[5]= i2c_readNak(); // letztes Byte lesen, darum kein ACK
	i2c_stop();           // Zugriff beenden
				
}
#endif

/*
	Routines for Serial communication:
*/
void uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

/*
	Send a character:
*/
void uart_putchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = c;
}

/*
	Receive a character:
*/
char uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

/*
	Send a String:
*/
void uart_putstring(char *s)
{
  int i;
  i=0;
  while(i<1024 && s[i]!='\0')
  {
	uart_putchar(s[i]);
	i++;
  }
}

void send_pstart()
{
	uart_putchar(0x10); // DLE - Data Link Escape
	uart_putchar(0x02); // STX - Start of Text
}

void send_pend()
{
	uart_putchar(0x10); // DLE - Data Link Escape
	uart_putchar(0x03); // ETX - End of Text
}

void send_data( uint8_t * data,int l)
{
	int i;
	for(i=0;i<l;i++) { uart_putchar(data[i]); }
}

/*
	Send a Package:
*/
void send_packet(uint8_t * data,int l)
{
	send_pstart();
	send_data(data,l);
	send_pend();
}


int main(void)
{
	uart_init();		// init Serial interface
	i2c_init();       	// init I2C interface
     
	// ack = i2cRead(BMA280_ADDRESS, 0x00, 1, &sig);
	//init_bma020();

	init_bma280();		// init Accelerometer
	timer_init();	 	// init Timer and start measurements

	 while(1) { } 
	// while(1) { uart_getchar(); read_bma280(); send_packet(rawADC,6);}

}



