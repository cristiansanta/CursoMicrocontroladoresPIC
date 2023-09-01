#include<16F887.h>
#use delay(clock=4000000)
#fuses xt,noprotect,nowdt,nobrownout,put,nolvp
#byte portb=6

void main()
{
  set_tris_b(0b00000000);
  portb=0;//comienzan apagados los pines del puerto B
  while(true)
  {
  portb=0b10000000;//Inicia RB7 encendido
    delay_ms(250);
    while(!bit_test(portb,0))//Mientras RB0 este apagado
    {portb=portb>>1;    //Empiece a rotar en una unidad hacia la DERECHA
     delay_ms(250);
    }
     
    while(!bit_test(portb,7))//Mientras RB7 este apagado
    {portb=portb<<1;    //Empiece a rotar en una unidad hacia la IZQUIERDA
     delay_ms(250);
    } 
     portb=0b10000001;
    delay_ms(250);
    portb=0b00000000;
    delay_ms(250);
    portb=0b01000010;
    delay_ms(250);
    portb=0b00000000;
    delay_ms(250);
    portb=0b00100100;
    delay_ms(250);
    portb=0b00000000;
    delay_ms(250);
    portb=0b00011000;//Inicia encendido 
    delay_ms(250);
    portb=0b00000000;
    delay_ms(250);
    
    
   
  }  
}
