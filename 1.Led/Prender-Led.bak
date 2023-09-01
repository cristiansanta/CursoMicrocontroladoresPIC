#INCLUDE <16f887.h>
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP
#DEFINE SW PORTA,1  //pin puerto A sera llamado SW
#DEFINE LED PORTB,0 //Puerto B RB0 se llama LED
#BYTE PORTA= 5//Lugar de memoria puerto A
#BYTE PORTB=6//Lugar de memoria puerto B

MAIN()
{
  SET_TRIS_A(0B10);
  SET_TRIS_B(0B11111110);//Configura puerto B 0=salida 1=input
   WHILE(TRUE)   //CICLO INFINITO
   { 
      IF(BIT_TEST(SW)){//PREGUNTA SI ESTA ACTIVADO
      BIT_SET(LED);   //PRENDE LED
      }
      ELSE// SINO SI ESTA DESACTIVADO APAGUE
      {
        BIT_CLEAR(LED);
      }
   }
}
     
