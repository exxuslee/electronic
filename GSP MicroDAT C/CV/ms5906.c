/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.4a Advanced
Automatic Program Generator
� Copyright 1998-2009 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 26.10.2010
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>
#include <delay.h>

#define pvv PORTC.0
#define got PORTC.1

#define prm PORTC.2
#define vdch PORTC.3

#define ust PINC.4
#define otv PINC.5

#define sh_data_in PIND
#define sh_data_out PORTD                            
#define sh_adr PORTB
#define KORZ_INP 0x000f
#define KORZ_OUT 0x00f0

// Declare your global variables here
char modul_00, modul_01, modul_10, modul_11, modul_20, modul_21, modul_30, modul_31;
char modul_40, modul_41, modul_50, modul_51, modul_60, modul_61, modul_70, modul_71;
unsigned int i;

void dannye()      //zapis i chtenie dannyh s modulej v korzine
    {
    // Place your code here
    for (sh_adr=0, i=1; sh_adr<=15;sh_adr++, i<<=1)
        {
        if ((KORZ_INP & i) == i)               //esli modul - vhodnoj, to
            {
            DDRD=0x00;                          //nastraivaem port na vhod
            prm=1;
            while (otv==0)
                {
                switch (sh_adr)
                    {
                    case 0 : modul_71=sh_data_in;
                    case 1 : modul_70=sh_data_in;
                    case 2 : modul_61=sh_data_in;
                    case 3 : modul_60=sh_data_in;
                    case 4 : modul_51=sh_data_in;
                    case 5 : modul_50=sh_data_in;
                    case 6 : modul_41=sh_data_in;
                    case 7 : modul_40=sh_data_in;
                    case 8 : modul_31=sh_data_in;
                    case 9 : modul_30=sh_data_in;
                    case 10 : modul_21=sh_data_in;
                    case 11 : modul_20=sh_data_in;
                    case 12 : modul_11=sh_data_in;
                    case 13 : modul_10=sh_data_in;
                    case 14 : modul_01=sh_data_in;
                    case 15 : modul_00=sh_data_in;
                    };
                };
            prm=0;
            };
        if ((KORZ_OUT & i) == i)        //esli modul - vyhodnoj, to
            {
            DDRD=0xff;                    //port na vihod
            vdch=1;
            while (otv==0)
                {
                switch (sh_adr)
                    {
                    case 0 : sh_data_out=modul_00;
                    case 1 : sh_data_out=modul_01;
                    case 2 : sh_data_out=modul_10;
                    case 3 : sh_data_out=modul_11;
                    case 4 : sh_data_out=modul_20;
                    case 5 : sh_data_out=modul_21;
                    case 6 : sh_data_out=modul_30;
                    case 7 : sh_data_out=modul_31;
                    case 8 : sh_data_out=modul_40;
                    case 9 : sh_data_out=modul_41;
                    case 10 : sh_data_out=modul_50;
                    case 11 : sh_data_out=modul_51;
                    case 12 : sh_data_out=modul_60;
                    case 13 : sh_data_out=modul_61;
                    case 14 : sh_data_out=modul_70;
                    case 15 : sh_data_out=modul_71;
                    };
                };        
            vdch=0;
            };
        };
    };

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x0F;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

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

pvv=1;
got=0;
while (ust==1) got=0;
got=1;
for (sh_adr=0, i=1; sh_adr<=15;sh_adr++, i<<=1)
    {
    if ((KORZ_INP & i) == i)               //esli modul - vhodnoj, to
            {
            DDRD=0x00;                          //nastraivaem port na vhod
            prm=1;
            while (otv==0);
            prm=0;
            };
    if ((KORZ_OUT & i) == i)        //esli modul - vyhodnoj, to
            {
            DDRD=0xff;                    //port na vihod
            vdch=1;
            while (otv==0);
            vdch=0;
            };
    };
pvv=0;

while (1)
      {
      // Place your code here
      char temp=0;

      dannye();

      temp=temp|modul_00;
      temp=temp|modul_01;
      temp=temp|modul_10;
      temp=temp|modul_11;
      temp=temp|modul_20;
      modul_21=temp;
      modul_30=temp;
      modul_31=temp;
      modul_40=temp;
      
      delay_ms (10);
      };
}
