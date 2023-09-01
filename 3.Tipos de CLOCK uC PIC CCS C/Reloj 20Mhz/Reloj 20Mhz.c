#INCLUDE <16f887.h>
#USE DELAY(clock=20MHz,crystal)// crystal=se toma el cristal externo
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP
#DEFINE LED PORTB,0 //Puerto B RB0 se llama LED
#byte PORTB=6//Lugar de memoria puerto B

MAIN()
{
  SET_TRIS_B(0);//CERO(0)==SALIDA UNO(1)==ENTRADA
  PORTB=0;
  WHILE(TRUE)
  {
    BIT_SET(LED);
    DELAY_MS(100);
    BIT_CLEAR(LED);
    DELAY_MS(100);
  }
}