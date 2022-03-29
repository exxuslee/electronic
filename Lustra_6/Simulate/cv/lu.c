#include <tiny13a.h>

unsigned int i=0;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
i++;
if (i==60000) i=0;
}



void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func5=In Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State5=T State4=0 State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x10;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 4,492 kHz
// Mode: Fast PWM top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x03;
TCCR0B=0x05;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-5: Off
GIMSK=0x00;
MCUCR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x02;

// Analog Comparator initialization
// Analog Comparator: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR0=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// Watchdog Timer initialization
// Watchdog Timer Prescaler: OSC/1024k
// Watchdog Timer interrupt: Off
#pragma optsize-
WDTCR=0x39;
WDTCR=0x29;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      if (i ==     0) PORTB.4=0;
      if (i ==   500) PORTB.4=1;      
      if (i == 16000) PORTB.4=0;
      #asm("wdr");
      }
}