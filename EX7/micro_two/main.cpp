
#include <mega16.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

char str[20];
char ch;
int i = 0;

int main(void)
{

while(1)
{
   ch = getchar();
   if(ch == '*')
   {
      while(ch != '#')
      {
         ch = getchar();
         str[i++] = ch;
      }
      str[--i] = NULL;
      lcd_puts(str);
      delay_ms(400);
      lcd_clear();
      i = 0;
   }
}
}