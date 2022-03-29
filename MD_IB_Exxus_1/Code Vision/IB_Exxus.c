/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
� Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 02.06.2009
Author  : 
Company : 
Comments: 


Chip type           : ATmega32
Program type        : Application
Clock frequency     : 8,000000 MHz
Memory model        : Small
External RAM size   : 0
Data Stack size     : 512
*****************************************************/

#include <mega32.h>

// Alphanumeric LCD Module functions
#asm
   .equ __lcd_port=0x15 ;PORTC
#endasm
#include <lcd.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>

#define ADC_VREF_TYPE 0x00
#define light PORTC.5

// Declare your global variables here
char string_LCD_1[20], string_LCD_2[20];
int x_1, x_2;
int faza, amplituda;
unsigned int zero_amplituda, zero_faza, viz_period, y_gnd, x_gnd;
float  gnd_amplituda, gnd_faza, rock_amplituda, rock_faza, now_amplituda, now_faza;
unsigned int period;
unsigned char vol, bar, menu, tik, gnd_rage;
unsigned char viz_amplituda, viz_faza;
unsigned int batt_celoe, batt_drob;
bit kn1, kn2, kn3, kn4, kn5, kn6;

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

void batt_zarqd(void)
    {
    unsigned int temp;
    #asm("wdr");
    temp=read_adc(3);
    batt_celoe=temp/10;
    batt_drob=temp%10;
    }

void kn_klava(void)
    {
    #asm("wdr");
    kn1=0;
    kn2=0;
    kn3=0;
    kn4=0;
    kn5=0;
    kn6=0;
    DDRD.4=1;
    PORTD.4=0;
    if (PIND.2==0 && PIND.3==0) kn1=1;
    if (PIND.2==1 && PIND.3==0) kn2=1;
    DDRD.4=0;
    DDRD.2=1;
    PORTD.4=1;
    PORTD.2=0;
    if (PIND.4==1 && PIND.3==0) kn3=1;
    if (PIND.4==0 && PIND.3==0) kn4=1;
    DDRD.2=0;
    DDRD.3=1;
    PORTD.2=1;
    PORTD.3=0;
    if (PIND.4==1 && PIND.2==0) kn5=1;
    if (PIND.4==0 && PIND.2==1) kn6=1;
    DDRD.3=0;
    PORTD.3=1;
    }
    
void lcd_disp(void)
    {
    #asm("wdr");
    if (menu==1)
        {
        light=1;
        lcd_gotoxy (0,0);
        sprintf (string_LCD_1, "%d.%dV V=%d B=%d   ", batt_celoe, batt_drob, vol, bar);
        lcd_puts (string_LCD_1);
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "%x %x   ", faza, amplituda);
        lcd_puts (string_LCD_2);
        return;        
        };
    if (menu==2)
        {
        light=1;
        lcd_gotoxy (0,0);
        sprintf (string_LCD_1, " TX calibration ");
        lcd_puts (string_LCD_1);
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "tik %d => %dHz", tik, viz_period);
        lcd_puts (string_LCD_2);
        return;        
        };
    if (menu==3)
        {
        light=1;
        lcd_gotoxy (0,0);
        sprintf (string_LCD_1, "> Ground rage  <");
        lcd_puts (string_LCD_1);
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, " %d              ", gnd_rage);
        lcd_puts (string_LCD_2);
        return;        
        };                        
    if (kn2==1)
        {
        light=1;
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "V%d", vol);
        lcd_puts (string_LCD_2);
        return;
        };
    if (kn3==1)
        {
        light=1;
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "B%d", bar);
        lcd_puts (string_LCD_2);
        return;
        }; 

    if (kn4==1)
        {
        light=1;
        lcd_gotoxy (0,0);
        sprintf (string_LCD_1, ">>>>> Rock <<<<<", bar);
        lcd_puts (string_LCD_1);
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "%f %f", rock_amplituda, rock_faza);
        lcd_puts (string_LCD_2);       
        return;
        };
        
    if (kn5==1)
        {
        light=1;
        lcd_gotoxy (0,0);
        sprintf (string_LCD_1, ">>>> Ground <<<<");
        lcd_puts (string_LCD_1);
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "%f %f ", gnd_amplituda, gnd_faza);
        lcd_puts (string_LCD_2);
        return;
        };
    if (kn6==1)
        {
        light=1;
        lcd_gotoxy (0,0);
        sprintf (string_LCD_1, ">>>>> Zero <<<<<");
        lcd_puts (string_LCD_1);
        lcd_gotoxy (0,1);
        sprintf (string_LCD_2, "%x %x %x %x ", zero_amplituda, zero_faza, amplituda, faza);
        lcd_puts (string_LCD_2);
        return;
        };   
    lcd_gotoxy (0,0);
    if (viz_amplituda==0)    sprintf (string_LCD_1, "                ");
    if (viz_amplituda==1)    sprintf (string_LCD_1, "_               ");    
    if (viz_amplituda==2)    sprintf (string_LCD_1, "�               ");
    if (viz_amplituda==3)    sprintf (string_LCD_1, "�_              ");    
    if (viz_amplituda==4)    sprintf (string_LCD_1, "��              ");
    if (viz_amplituda==5)    sprintf (string_LCD_1, "��_             ");    
    if (viz_amplituda==6)    sprintf (string_LCD_1, "���             ");
    if (viz_amplituda==7)    sprintf (string_LCD_1, "���_            ");    
    if (viz_amplituda==8)    sprintf (string_LCD_1, "����            ");
    if (viz_amplituda==9)    sprintf (string_LCD_1, "����_           ");    
    if (viz_amplituda==10)   sprintf (string_LCD_1, "�����           ");
    if (viz_amplituda==11)   sprintf (string_LCD_1, "�����_          ");    
    if (viz_amplituda==12)   sprintf (string_LCD_1, "������          ");
    if (viz_amplituda==13)   sprintf (string_LCD_1, "������_         ");    
    if (viz_amplituda==14)   sprintf (string_LCD_1, "�������         ");
    if (viz_amplituda==15)   sprintf (string_LCD_1, "�������_        ");    
    if (viz_amplituda==16)   sprintf (string_LCD_1, "��������        ");
    if (viz_amplituda==17)   sprintf (string_LCD_1, "��������_       ");    
    if (viz_amplituda==18)   sprintf (string_LCD_1, "���������       ");
    if (viz_amplituda==19)   sprintf (string_LCD_1, "���������_      ");    
    if (viz_amplituda==20)   sprintf (string_LCD_1, "����������      ");
    if (viz_amplituda==21)   sprintf (string_LCD_1, "����������_     ");    
    if (viz_amplituda==22)   sprintf (string_LCD_1, "�����������     ");
    if (viz_amplituda==23)   sprintf (string_LCD_1, "�����������_    ");    
    if (viz_amplituda==24)   sprintf (string_LCD_1, "������������    ");
    if (viz_amplituda==25)   sprintf (string_LCD_1, "������������_   ");    
    if (viz_amplituda==26)   sprintf (string_LCD_1, "�������������   ");
    if (viz_amplituda==27)   sprintf (string_LCD_1, "�������������_  ");    
    if (viz_amplituda==28)   sprintf (string_LCD_1, "��������������  ");
    if (viz_amplituda==29)   sprintf (string_LCD_1, "��������������_ ");   
    if (viz_amplituda==30)   sprintf (string_LCD_1, "��������������� ");
    if (viz_amplituda==31)   sprintf (string_LCD_1, "���������������_");    
    if (viz_amplituda==32)   sprintf (string_LCD_1, "����������������");    
    lcd_puts (string_LCD_1);
    lcd_gotoxy (0,1);
    if (viz_faza==0)  sprintf (string_LCD_2, "   �-----#-----�");
    if (viz_faza==1)  sprintf (string_LCD_2, "   �----#I-----�");
    if (viz_faza==2)  sprintf (string_LCD_2, "   �---#-I-----�");
    if (viz_faza==3)  sprintf (string_LCD_2, "   �--#--I-----�");
    if (viz_faza==4)  sprintf (string_LCD_2, "   �-#---I-----�");
    if (viz_faza==5)  sprintf (string_LCD_2, "   �#----I-----�");
    if (viz_faza==6)  sprintf (string_LCD_2, "   �-----I#----�");
    if (viz_faza==7)  sprintf (string_LCD_2, "   �-----I-#---�");
    if (viz_faza==8)  sprintf (string_LCD_2, "   �-----I--#--�");
    if (viz_faza==9)  sprintf (string_LCD_2, "   �-----I---#-�");
    if (viz_faza==10) sprintf (string_LCD_2, "   �-----I----#�");
    lcd_puts (string_LCD_2);    
    light=0;
    }

void real_faza_i_amp (void)
    {
    while (ACSR.5==0);
    while (ACSR.5==1);
    while (ACSR.5==0);
    while (ACSR.5==1)
        {
        x_1=TCNT1;
        PORTA.7=1;
        };
    while (ACSR.5==0)
        {
        x_2=TCNT1;
        PORTA.7=0;
        };
    if (x_2 > x_1) faza= (x_2 + x_1) / 2;
    if (x_2 < x_1)
        {
        faza= (x_1 - x_2) + (x_1 + x_2) / 2;
        if (faza > period) faza = faza - period;   // ICR1
        };
    while (TCNT1 != faza); 
    PORTA.6=1;
    amplituda=read_adc(0);
    PORTA.6=0;
    }
    
float vektor_amp (unsigned int koord_1_1, unsigned int koord_1_2, unsigned int koord_2_1, unsigned int koord_2_2)
    {
    long int Y;
    long int X;
    long unsigned int temp3;
    float temp;
    koord_1_1 = koord_1_1 /2;
    koord_1_2 = koord_1_2 /2;
    koord_2_1 = koord_2_1 /2;
    koord_2_2 = koord_2_2 /2;
    if (koord_1_1 > koord_2_1) Y = koord_1_1 - koord_2_1;
    else Y = koord_2_1 - koord_1_1;
    if (koord_1_2 > koord_2_2) X = koord_1_2 - koord_2_2;
    else X = koord_2_2 - koord_1_2; 
    temp3  = Y*Y + X*X;
    temp = sqrt (temp3); 
    return temp;
    }

    
float vektor_faza (unsigned int koord_1_1, unsigned int koord_1_2, unsigned int koord_2_1, unsigned int koord_2_2)
    {
    signed int Y;
    signed int X;
    float temp;
    Y = koord_1_1 - koord_2_1;
    X = koord_1_2 - koord_2_2;
    temp = atan2 (Y,X);    
    return temp;
    } 
    
float th_cos (float a, float aa_x, float b, float bb_x)
    {
    float c;
    float aabb;
    aabb = aa_x - bb_x;
    c = sqrt (a*a + b*b - 2*a*b*cos(aabb));
    return c;
    }   

float th_sin (float c, int b_y, int b_x, int c_y, int c_x)
    {
    int ab;
    float temp;
    if (b_y > c_y) ab = b_y - c_y;
    else ab = c_y - b_y; 
    temp = asin (ab/c);
    if (c_x > b_x) temp = 3.141593 - temp;
    return temp;
    }   

void main_menu(void)
    {
    #asm("wdr");
    menu++;
    if (menu==255) menu=3;
    if (menu==4) menu=0;
    while (kn1==1) 
        {
        kn_klava();
        lcd_disp();
        };
    }
    
void volume(void)
    {
    #asm("wdr");
    if (menu==2) tik++;
    if (menu==3) gnd_rage++;
    else vol++;
    if (vol==4) vol=0;
    while (kn2==1) 
        {
        kn_klava();
        lcd_disp();
        };
    }    

void barrier(void)
    {
    #asm("wdr");
    if (menu==2) tik--;
    if (menu==3) gnd_rage--;
    else bar++;
    if (bar==255) bar=9;
    if (bar==10) bar=0;
    while (kn3==1) 
        {
        kn_klava();
        lcd_disp();
        };
    }

void rock(void)
    {
    #asm("wdr");
    rock_amplituda = vektor_amp(amplituda, faza, zero_amplituda, zero_faza);
    rock_faza = vektor_faza(amplituda, faza, zero_amplituda, zero_faza);
    }

void ground(void)
    {
    #asm("wdr");
    y_gnd = amplituda;
    x_gnd = faza;
    gnd_amplituda = vektor_amp(amplituda, faza, zero_amplituda, zero_faza);
    gnd_faza = vektor_faza(amplituda, faza, zero_amplituda, zero_faza);
    }

void zero(void)
    {
    #asm("wdr");
    zero_amplituda=0;
    zero_faza=0xFA1;
//    zero_amplituda=amplituda;
//    zero_faza=faza;
    }
    
void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0xC0;

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
// Func7=Out Func6=In Func5=Out Func4=In Func3=In Func2=In Func1=In Func0=Out 
// State7=0 State6=T State5=0 State4=T State3=T State2=T State1=T State0=0 
PORTD=0x00;
DDRD=0xA1;

// Analog Comparator initialization
// Analog Comparator: On
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x00;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000,000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x83;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Phase correct PWM top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Fast PWM top=ICR1
// OC1A output: Non-Inv.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x82;
TCCR1B=0x19;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x1F;
ICR1L=0x42;
OCR1AH=0x00;
OCR1AL=0x0F;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Phase correct PWM top=FFh
// OC2 output: Non-Inverted PWM
ASSR=0x00;
TCCR2=0x61;
TCNT2=0x00;
OCR2=0x7F;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x0C;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x08;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;

// Watchdog Timer initialization
// Watchdog Timer Prescaler: OSC/2048k
WDTCR=0x0F;                     //0f

// LCD module initialization
lcd_init(16);

#asm("wdr");

lcd_gotoxy (0,0);
sprintf (string_LCD_1, "$$$ MD_Exxus $$$");
lcd_puts (string_LCD_1);
lcd_gotoxy (0,1);
sprintf (string_LCD_2, "   v0.4   ^_^   ");
lcd_puts (string_LCD_2);
delay_ms (500);

tik=51;
period=0x1F42;
x_gnd=period/2;
zero_faza=period/2;

while (1)
      {
      // Place your code here
      float temp_amplituda;
      float temp_faza;
      #asm("wdr");
      real_faza_i_amp ();
      kn_klava();
      if (kn1==1) main_menu();
      if (kn2==1) volume();
      if (kn3==1) barrier();
      if (kn4==1) rock();   
      if (kn5==1) ground();  
      if (kn6==1) zero();

      
      viz_period = period / 8;
      
      now_amplituda= vektor_amp (amplituda, faza, zero_amplituda, zero_faza);
      now_faza= vektor_faza (amplituda, faza, zero_amplituda, zero_faza);

      temp_amplituda = th_cos (now_amplituda, now_faza, gnd_amplituda, gnd_faza);
      temp_faza = th_sin (temp_amplituda, amplituda, faza, y_gnd, x_gnd);


//      temp_amplituda= temp_amplituda - gnd_amplituda;
//      temp_faza= temp_faza - gnd_faza;      
      if (temp_amplituda> 2079 ) viz_amplituda=32;
      else if (temp_amplituda> 2016 ) viz_amplituda=31;      
      else if (temp_amplituda> 1953 ) viz_amplituda=30;
      else if (temp_amplituda> 1890 ) viz_amplituda=29; 
      else if (temp_amplituda> 1827 ) viz_amplituda=28; 
      else if (temp_amplituda> 1764 ) viz_amplituda=27; 
      else if (temp_amplituda> 1701 ) viz_amplituda=26; 
      else if (temp_amplituda> 1638 ) viz_amplituda=25; 
      else if (temp_amplituda> 1575 ) viz_amplituda=24; 
      else if (temp_amplituda> 1512 ) viz_amplituda=23; 
      else if (temp_amplituda> 1449 ) viz_amplituda=22; 
      else if (temp_amplituda> 1386 ) viz_amplituda=21;
      else if (temp_amplituda> 1323 ) viz_amplituda=20;
      else if (temp_amplituda> 1260 ) viz_amplituda=19;
      else if (temp_amplituda> 1197 ) viz_amplituda=18; 
      else if (temp_amplituda> 1134 ) viz_amplituda=17; 
      else if (temp_amplituda> 1071 ) viz_amplituda=16; 
      else if (temp_amplituda> 1008 ) viz_amplituda=15; 
      else if (temp_amplituda> 945  ) viz_amplituda=14; 
      else if (temp_amplituda> 882  ) viz_amplituda=13; 
      else if (temp_amplituda> 819  ) viz_amplituda=12; 
      else if (temp_amplituda> 756  ) viz_amplituda=11; 
      else if (temp_amplituda> 693  ) viz_amplituda=10;
      else if (temp_amplituda> 630  ) viz_amplituda=9;
      else if (temp_amplituda> 567  ) viz_amplituda=8;
      else if (temp_amplituda> 504  ) viz_amplituda=7;
      else if (temp_amplituda> 441  ) viz_amplituda=6;
      else if (temp_amplituda> 378  ) viz_amplituda=5;
      else if (temp_amplituda> 315  ) viz_amplituda=4; 
      else if (temp_amplituda> 252  ) viz_amplituda=3; 
      else if (temp_amplituda> 189  ) viz_amplituda=2; 
      else if (temp_amplituda> 126  ) viz_amplituda=1; 
      else if (temp_amplituda> 63   ) viz_amplituda=0; 
       
      if (temp_faza> 3.14) viz_faza=0;
      else if (temp_faza> 2.86) viz_faza=5;
      else if (temp_faza> 2.57) viz_faza=4;
      else if (temp_faza> 2.28) viz_faza=3;
      else if (temp_faza> 2.00) viz_faza=2;
      else if (temp_faza> 1.71) viz_faza=1;
      else if (temp_faza> 1.43) viz_faza=0;
      else if (temp_faza> 1.14) viz_faza=6;
      else if (temp_faza> 0.86) viz_faza=7;
      else if (temp_faza> 0.57) viz_faza=8;
      else if (temp_faza> 0.29) viz_faza=9; 
      else if (temp_faza> 0.00) viz_faza=10;     
             
      batt_zarqd();
      lcd_disp();

      #asm("wdr");
      };
}
