#include<16f887.h>
#fuses XT,NOPROTECT,NOWRT,NOPUT,NOWDT,NOLVP,NOCPD //ORDENES PARA EL PROGRAMADOR
#use delay(clock=4000000)
#include <lcd.c>

const char message[]={"Cristian Andres Calambas Santa"};//Vector Unidimensional

void main(void)
{
   char y=1;//indice fila
   signed char x=16;//indice columnas(posiciones)
   lcd_init();
   
   while(true)
   { 
     lcd_gotoxy(x,y);//x=column  Y=fila
     lcd_putc(message);
     delay_ms(100);
     x--;
     if(x<-30)
     {
      x=16;
      y++;
      if(y>2)
      {
        y=1;
      }
     }
     lcd_putc("\f");//Limpia pantalla
   }//......Ciclo INFINITO
}
