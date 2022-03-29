
#pragma used+
sfrb ADCSRB=0x03;
sfrb ADCL=0x04;
sfrb ADCH=0x05;
sfrw ADCW=0x04; 
sfrb ADCSRA=0x06;
sfrb ADMUX=0x07;
sfrb ACSR=0x08;
sfrb DIDR0=0x14;
sfrb PCMSK=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEAR=0x1e;
sfrb WDTCR=0x21;
sfrb PRR=0x25;
sfrb CLKPR=0x26;
sfrb GTCCR=0x28;
sfrb OCR0B=0x29;
sfrb DWDR=0x2e;
sfrb TCCR0A=0x2f;
sfrb BODCR=0x30;
sfrb OSCCAL=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0B=0x33;
sfrb MCUSR=0x34;
sfrb MCUCR=0x35;
sfrb OCR0A=0x36;
sfrb SPMCSR=0x37;
sfrb TIFR0=0x38;
sfrb TIMSK0=0x39;
sfrb GIFR=0x3a;
sfrb GIMSK=0x3b;
sfrb SPL=0x3d;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x18
	.EQU __sm_adc_noise_red=0x08
	.EQU __sm_powerdown=0x10
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

unsigned int i=0;

interrupt [4] void timer0_ovf_isr(void)
{

i++;
if (i==60000) i=0;
}

void main(void)
{

#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#pragma optsize+

PORTB=0x00;
DDRB=0x10;

TCCR0A=0x03;
TCCR0B=0x05;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

GIMSK=0x00;
MCUCR=0x00;

TIMSK0=0x02;

ACSR=0x80;
ADCSRB=0x00;
DIDR0=0x00;

ADCSRA=0x00;

#pragma optsize-
WDTCR=0x39;
WDTCR=0x29;
#pragma optsize+

#asm("sei")

while (1)
{

if (i ==     0) PORTB.4=0;
if (i ==   500) PORTB.4=1;      
if (i == 16000) PORTB.4=0;
#asm("wdr");
}
}
