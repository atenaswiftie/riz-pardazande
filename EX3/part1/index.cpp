#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU16000000UL

char segment[10]={
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};

int main(void) 
{
    PORTC=0xff;
    int i=0;
    _delay_ms(1000);
    while (1)
    {
       i+=1;
       PORTC=segment[i];
       if(i>9) 
       i=0;
    }
}