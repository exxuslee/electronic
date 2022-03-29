/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
� Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 15.03.2010
Author  : 
Company : 
Comments: 


Chip type           : ATmega32
Program type        : Application
Clock frequency     : 16,384000 MHz
Memory model        : Small
External RAM size   : 0
Data Stack size     : 512
*****************************************************/

#include <mega32.h>
    #asm
        .equ __i2c_port=0x15
        .equ __sda_bit=1
        .equ __scl_bit=0
    #endasm
#include <i2c.h>
/*
unsigned char porqdok = 0;

// 2 Wire bus interrupt service routine
interrupt [TWI] void twi_isr(void)
{
// Place your code here
//TWCR &= 0xFE;

if (porqdok == 0)
    {
    TWDR = 0xaa;
    TWCR |= 0x84;
    PORTA.0 = 1;
    PORTA.0 = 0;
    return;
    };

if (porqdok == 1)
    {
    TWDR = 0xbb;
    TWCR |= 0x84;
    PORTA.0 = 1;
    PORTA.0 = 0;
    return;
    };

if (porqdok == 2)
    {
    TWDR = 0xcc;
    TWCR |= 0x84;
    PORTA.0 = 1;
    PORTA.0 = 0;
    return;
    };

if (porqdok == 3)
    {
    TWDR = 0xdd;
    TWCR |= 0x84;
    PORTA.0 = 1;
    PORTA.0 = 0;
    return;
    };

porqdok= porqdok+1;
if (porqdok == 4) porqdok = 0;
return;
}
*/

// 2 Wire bus interrupt service routine
interrupt [TWI] void twi_isr(void)
{
// Place your code here
//TWCR &= 0xFE;

TWDR = 0xaa;
TWCR |= 0x84;

PORTA.0 = 1;
PORTA.0 = 0;

while (!(TWCR & 0x80));

TWDR = 0xbb;
TWCR |= 0x84;

PORTA.0 = 1;
PORTA.0 = 0;

while (!(TWCR & 0x80));

TWDR = 0xcc;
TWCR |= 0x84;

PORTA.0 = 1;
PORTA.0 = 0;

while (!(TWCR & 0x80));

TWDR = 0xdd;
TWCR |= 0x84;

PORTA.0 = 1;
PORTA.0 = 0;

while (!(TWCR & 0x80));
TWCR |= 0x80;

PORTA.0 = 1;
PORTA.0 = 0;

//return;
}


// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x03;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer 2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// 2 Wire Bus initialization
// Generate Acknowledge Pulse: On
// 2 Wire Bus Slave Address: 44h
// General Call Recognition: Off
// Bit Rate: 390,095 kHz
TWSR=0x00;
TWBR=0x0D;
TWAR=0x88;
TWCR=0x45;

// Global enable interrupts
#asm("sei")


while (1)
      {
      // Place your code here
      #asm ("wdr")

      };
}
