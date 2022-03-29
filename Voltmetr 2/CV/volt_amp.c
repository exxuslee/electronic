/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.4a Advanced
Automatic Program Generator
� Copyright 1998-2009 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 29.07.2012
Author  : NeVaDa
Company : MICROSOFT
Comments:


Chip type               : ATmega8A
AVR Core Clock frequency: 16,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*****************************************************/

#include <mega8.h>
#include <delay.h>

#define _beep PORTD.3
#define _0 PORTD.0
#define _1 PORTC.1
#define _2 PORTC.2
#define _3 PORTB.2
#define _4 PORTD.7
#define _5 PORTD.6

#define _A PORTB.1
#define _B PORTD.5
#define _C PORTB.4
#define _D PORTD.2
#define _E PORTD.1
#define _F PORTB.0
#define _G PORTB.5
#define _P PORTB.3
#define ADC_VREF_TYPE 0x40

// Declare your global variables here
unsigned char seg0, seg1, seg2, seg3, seg4, seg5, i, j;
//unsigned int adc_data;
unsigned int in_v=0, in_a=0;
unsigned int in01=0, in02=0, in03=0, in04=0;
unsigned int in11=0, in12=0, in13=0, in14=0;
unsigned int in21=0, in22=0, in23=0, in24=0;
eeprom float vol_cor, amp_cor;

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

void codegen (char x, char y)
{
     if (y==0)  _A=1,_B=1,_C=1,_D=1,_E=1,_F=1,_G=0;
else if (y==1)  _A=0,_B=1,_C=1,_D=0,_E=0,_F=0,_G=0;
else if (y==2)  _A=1,_B=1,_C=0,_D=1,_E=1,_F=0,_G=1;
else if (y==3)  _A=1,_B=1,_C=1,_D=1,_E=0,_F=0,_G=1;
else if (y==4)  _A=0,_B=1,_C=1,_D=0,_E=0,_F=1,_G=1;
else if (y==5)  _A=1,_B=0,_C=1,_D=1,_E=0,_F=1,_G=1;
else if (y==6)  _A=1,_B=0,_C=1,_D=1,_E=1,_F=1,_G=1;
else if (y==7)  _A=1,_B=1,_C=1,_D=0,_E=0,_F=0,_G=0;
else if (y==8)  _A=1,_B=1,_C=1,_D=1,_E=1,_F=1,_G=1;
else if (y==9)  _A=1,_B=1,_C=1,_D=1,_E=0,_F=1,_G=1;
else            _A=0,_B=0,_C=0,_D=0,_E=0,_F=0,_G=0;

     if (x==0) _0=0, _1=1, _2=1, _3=1, _4=1, _5=1, _P=0;
else if (x==1) _0=1, _1=0, _2=1, _3=1, _4=1, _5=1, _P=1;
else if (x==2) _0=1, _1=1, _2=0, _3=1, _4=1, _5=1, _P=0;

else if (x==3) _0=1, _1=1, _2=1, _3=0, _4=1, _5=1, _P=1;
else if (x==4) _0=1, _1=1, _2=1, _3=1, _4=0, _5=1, _P=0;
else           _0=1, _1=1, _2=1, _3=1, _4=1, _5=0, _P=0;

delay_us(100);
_0=1, _1=1, _2=1, _3=1, _4=1, _5=1;
return;
}

void read(void)
{
in01 = in02;
in02 = in03;
in03 = in04;
in04 = in11;
in11 = in12;
in12 = read_adc(6);
in_v = (in01+in02+in03+in04+in11+in12)/6;

in13 = in14;
in14 = in21;
in21 = in22;
in22 = in23;
in23 = in24;
in24 = read_adc(7);
in_a = (in13+in14+in21+in22+in23+in24)/6;
return;
}

void preobr(float a, float b)
{
a = a / vol_cor;
     if (a >= 900)   seg0=9, a=a - 900;
else if (a >= 800)   seg0=8, a=a - 800;
else if (a >= 700)   seg0=7, a=a - 700;
else if (a >= 600)   seg0=6, a=a - 600;
else if (a >= 500)   seg0=5, a=a - 500;
else if (a >= 400)   seg0=4, a=a - 400;
else if (a >= 300)   seg0=3, a=a - 300;
else if (a >= 200)   seg0=2, a=a - 200;
else if (a >= 100)   seg0=1, a=a - 100;
else                 seg0=10;

if      (a >= 90)    seg1=9, a=a-90;
else if (a >= 80)    seg1=8, a=a-80;
else if (a >= 70)    seg1=7, a=a-70;
else if (a >= 60)    seg1=6, a=a-60;
else if (a >= 50)    seg1=5, a=a-50;
else if (a >= 40)    seg1=4, a=a-40;
else if (a >= 30)    seg1=3, a=a-30;
else if (a >= 20)    seg1=2, a=a-20;
else if (a >= 10)    seg1=1, a=a-10;
else                 seg1=0;

if      (a == 9)     seg2=9;
else if (a == 8)     seg2=8;
else if (a == 7)     seg2=7;
else if (a == 6)     seg2=6;
else if (a == 5)     seg2=5;
else if (a == 4)     seg2=4;
else if (a == 3)     seg2=3;
else if (a == 2)     seg2=2;
else if (a == 1)     seg2=1;
else                 seg2=0;

b = b / amp_cor;
if (b >=1000)
    {
    if (j > 127) seg3=9, seg4=9, seg5=9, _beep=1;
        else seg3=10, seg4=10, seg5=10, _beep=0;
    return;
    }
_beep=0;

     if (b >= 900)   seg3=9, b=b - 900;
else if (b >= 800)   seg3=8, b=b - 800;
else if (b >= 700)   seg3=7, b=b - 700;
else if (b >= 600)   seg3=6, b=b - 600;
else if (b >= 500)   seg3=5, b=b - 500;
else if (b >= 400)   seg3=4, b=b - 400;
else if (b >= 300)   seg3=3, b=b - 300;
else if (b >= 200)   seg3=2, b=b - 200;
else if (b >= 100)   seg3=1, b=b - 100;
else                 seg3=0;

if      (b >= 90)    seg4=9, b=b-90;
else if (b >= 80)    seg4=8, b=b-80;
else if (b >= 70)    seg4=7, b=b-70;
else if (b >= 60)    seg4=6, b=b-60;
else if (b >= 50)    seg4=5, b=b-50;
else if (b >= 40)    seg4=4, b=b-40;
else if (b >= 30)    seg4=3, b=b-30;
else if (b >= 20)    seg4=2, b=b-20;
else if (b >= 10)    seg4=1, b=b-10;
else                 seg4=0;

if      (b == 9)     seg5=9;
else if (b == 8)     seg5=8;
else if (b == 7)     seg5=7;
else if (b == 6)     seg5=6;
else if (b == 5)     seg5=5;
else if (b == 4)     seg5=4;
else if (b == 3)     seg5=3;
else if (b == 2)     seg5=2;
else if (b == 1)     seg5=1;
else                 seg5=0;

return;
}

void start(void)
{
// Input/Output Ports initialization
// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=In
// State6=T State5=P State4=P State3=P State2=0 State1=0 State0=P
PORTC=0x39;
DDRC=0x06;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
PORTD=0x00;
DDRD=0xFF;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
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
// Clock value: Timer2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 250,000 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x86;

// Global enable interrupts
//#asm("sei")
if (vol_cor == 0xFFFFFFFF) vol_cor = 4.00;
if (amp_cor == 0xFFFFFFFF) amp_cor = 1.00;
return;
}

void main(void)
{
start ();

while (1)
      {
      // Place your code here
      read();
      if (i == 0) preobr(in_v, in_a);

      codegen(0,seg0);
      codegen(1,seg1);
      codegen(2,seg2);
      codegen(3,seg3);
      codegen(4,seg4);
      codegen(5,seg5);

      codegen(1,seg1);
      codegen(2,seg2);
      codegen(0,seg0);
      codegen(4,seg4);
      codegen(5,seg5);
      codegen(3,seg3);

      codegen(2,seg2);
      codegen(0,seg0);
      codegen(1,seg1);
      codegen(5,seg5);
      codegen(3,seg3);
      codegen(4,seg4);

      i++;
      if (i>=50)
        {
        if (PORTC.0 == 0) vol_cor=+0.01;
        if (PORTC.3 == 0) vol_cor=-0.01;
        if (PORTC.4 == 0) amp_cor=+0.01;
        if (PORTC.5 == 0) amp_cor=-0.01;
        i=0;
        };
      j=j+4;

      };
}
