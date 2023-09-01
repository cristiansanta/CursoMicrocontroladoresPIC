#INCLUDE <16F887.H>
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP

byte const display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
#BYTE PORTB=6
int Contador;

main()
{
  SET_TRIS_B(0B00000000);//SE CONFIGURAN TODOS COMO SALIDA
  Contador=0;
  while(Contador<10)
  {
   PORTB=display[Contador];
   Contador++;
   DELAY_MS(500);
   if(Contador==10)
  {Contador=0;
  }
  }
  
}
