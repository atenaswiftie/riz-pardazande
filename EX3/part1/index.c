#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU16000000UL

char 7segment[10]={
    0x3f,0x06,0x5b,0x47,0x66,0x4d,0x7d,0x07
}

int main(void){
    PORTC=0xff;
 int i=0;

    while (1)
    {
       PORTC=7segment[i];
       if(i>10) 
       i=0
    }
}