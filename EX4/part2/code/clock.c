#include <mega32.h>
#include <stdio.h>
#include <delay.h>
#include <alcd.h>

#define LED PORTC.0

int showTime(int hour,int minute,int second);

int hour = 0;
int minute = 0;
int second = 0;

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{

    TCNT1H=0xCEFF >> 8;
    TCNT1L=0xCEFF & 0xff;
    second = second + 1;
    if(second >= 60){
        second = 0;
        minute += 1;
        if(minute >= 60){
                minute = 0;
                hour += 1;
                if(hour >= 24)
                    hour = 0;
        }
    }  
        showTime(hour,minute,second);
}


interrupt [EXT_INT1] void ext_int1_isr(void)
{
        minute += 1;
        if(minute >= 60){
            minute = 0;
            hour += 1;
            if(hour >= 24)
                hour = 0;
        }
        showTime(hour,minute,second); 
     
}


interrupt [EXT_INT2] void ext_int2_isr(void)
{

      minute-=1;
      if(minute<0){
          minute = 59;
          hour-=1;
          if(hour<0)
            hour = 23;
          }
      showTime(hour,minute,second); 
}


void main(void)
{
DDRA  = 0x00;
PORTA = 0x00;
DDRB  = 0x00;
PORTB = 0x00;


DDRC  = (0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (1<<DDC0);
PORTC = 0x00;

DDRD  = 0x00;
PORTD = 0x00;


TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;



TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0xCE;
TCNT1L=0xFF;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);


GICR|=(1<<INT1) | (1<<INT0) | (1<<INT2);
MCUCR=(1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00);
MCUCSR=(1<<ISC2);
GIFR=(1<<INTF1) | (1<<INTF0) | (1<<INTF2);

// USART initialization
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);

// Analog Comparator initialization
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);


lcd_init(8);

// Global enable interrupts
#asm("sei")

while (1)
      {
       
      }
}

 int showTime(int hour,int minute,int second){
    unsigned char time[15]; 
    lcd_gotoxy(0,0);
    lcd_puts("clock");
    lcd_gotoxy(0,1);
    sprintf(time,"%d%d:%d%d:%d%d",hour/10,hour%10,minute/10,minute%10,second/10,second%10);
    lcd_puts(time);
    return 0;
}


