#include "LCD.h"

char Read2Nib()
{
	char HNib, LNib;
	
	DATA_O |= 0xF0;
	sbi(CTRL,EN); //enable
	
	DDR_DATA =0x0F; // set 4 bit cao cua PORT DATA lam input // DDRB = 0b0000 1111
	HNib= DATA_I & 0xF0;
	cbi(CTRL,EN); //disable
	
	sbi(CTRL,EN); //enable
	LNib = DATA_I & 0xF0;
	cbi(CTRL,EN); //disable
	LNib>>=4;
	return (HNib|LNib);
}

void Write2Nib(uint8_t chr)
{

	uint8_t HNib, LNib, temp_data;
	temp_data=DATA_O & 0x0F; // doc 4 bit thap cua DATA_O de mask

	HNib=chr & 0xF0;
	LNib=(chr<<4) & 0xF0;
	
	DATA_O =(HNib |temp_data);
	sbi(CTRL,EN); //enable
	cbi(CTRL,EN); //disable
	
	DATA_O =(LNib|temp_data);
	sbi(CTRL,EN); //enable
	cbi(CTRL,EN); //disable
}

void Write8Bit(uint8_t chr)
{
	DATA_O=chr;   //out 8 bits to DATA Line
	sbi(CTRL,EN); //enable
	cbi(CTRL,EN); //disable
}

void wait_LCD()
{
	_delay_ms(100); // wait to output data each 100ms , this line better than above algorithm
	
}

void init_LCD()
{
	DDR_CTRL=0xFF;
	DDR_DATA=0xFF;
	
	//Function set------------------------------------------------------------------------------
	cbi(CTRL,RS);   // the following data is COMMAND
	cbi(CTRL, RW); // AVR->LCD
	cbi(CTRL, EN);
	
	sbi(CTRL,EN); //enable
	sbi(DATA_O, 5);
	cbi(CTRL,EN); //disable
	wait_LCD();
	Write2Nib(0x28);//4 bit mode 2line, 5x8 font
	wait_LCD();
	
	//Display control-------------------------------------------------------------------------
	cbi(CTRL,RS); // the following data is COMMAND
	Write2Nib(0x0E); //not Cursor display, 0x0E: with cursor
	wait_LCD();

	//Entry mode set------------------------------------------------------------------------
	cbi(CTRL,RS); // the following data is COMMAND
	Write2Nib(0x06);
	wait_LCD();

}

void clr_LCD() // xoa LCD
{
	cbi(CTRL,RS); //RS=0 mean the following data is COMMAND (not normal DATA)
	Write2Nib(0x01);
	wait_LCD();
	
}




void putChar_LCD(uint8_t chr)  // output character 1 by 1
{
	sbi(CTRL,RS); //this is a normal DATA
	Write2Nib(chr);
	wait_LCD();
}

void print_LCD(char* str)   // output a string
{
	unsigned char i;
	for (i=0; str[i]!=0; i++)
	{ putChar_LCD(str[i]);}
}

int main(void)
{

	
	init_LCD(); 
	print_LCD("hellooooo word  :))) "); 

    while (1) 
    { }
		
   
}

