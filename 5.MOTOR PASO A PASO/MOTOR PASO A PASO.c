#include<16F887.h>
//#use delay(clock=4000000)//crystal = interno
#use delay(clock=4000000,crystal)//crystal externo 4MHz de cuarzo es mas preciso
#fuses xt,noprotect,nowdt,nobrownout,put,nolvp,WRT

#byte portb=6//direcciones de memoria
#byte portc=7//direcciones de memoria
#define SW PORTC,0

int cont;
byte const Horario[4]={0b1100,
                       0b0110,
                       0b0011,
                       0b1001};
                       
byte const Anti_Ho[4]={0b1001,
                       0b0011,
                       0b0110,
                       0b1100};
 
main() 
{
  SET_TRIS_C(0B11111111);//SE CONFIGURAN TODOS COMO ENTRADA
  SET_TRIS_B(0B00000000);//SE CONFIGURAN TODOS COMO SALIDA
  WHILE(TRUE)
  {
     IF(BIT_TEST(SW))//pregunta si SW esta encendido
     {
      CONT=0;//contador en cero(0)
      WHILE((CONT<4)&&(BIT_TEST(SW)))//mientras cont sea menor a 4
      {                             //y SW este encendido
        PORTB=(Horario[CONT]);
        DELAY_MS(100);
        CONT++;
      }
     }ELSE   //De lo contrario 
      { CONT=0;                         //mientras cont sea menor a 4
        WHILE((CONT<4)&&(!BIT_TEST(SW)))//y SW este apagado
        {PORTB=(Anti_Ho[CONT]); 
         DELAY_MS(100);
         CONT++;
        }
      }
  }
}
