#INCLUDE <16F887.h>
//#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP
#USE DELAY(CLOCK=4000000,crystal)//Crystal Externo 4MHz
//#USE RS232(UART1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
Byte const Display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
#DEFINE USE_PORTB_KBD //Se va a utilizar un teclado
#INCLUDE <KBD.C>
#BYTE PORTC= 7
#BYTE PORTB= 6
//PARA CONFIGURAR RESISTENCIAS INTERNAS EN EL uC 16F887
#BYTE WPUB= 0X95 //eclarar registro option
#BYTE OPTION_REG= 0X81

char K;//Almacenar la informacion obtenida del teclado telefonico

void main()
{
 //PORT_B_PULLUPS(TRUE);//PARA EL 16F887 NO SIRVE ESTA INSTRUCCION //Habilitar resistencias internas de los 1ros 4 puertos de RB
 OPTION_REG = 0;//En el main se desactiva el registro OPTION
 WPUB=0B11111111;// y se seleccionan los PULLUPS que se van a utilizar
 KBD_INIT();//inicializar funcion de la libreria KBD.C para el teclado
 SET_TRIS_C(0);//Configurar el puerto C como salida
 PORTC=(DISPLAY[0]);
 while(true)
 { 
   K=0;
   K=KBD_GETC();//Captura cualquier tecla presionada
  // printf("%c",K);
   switch(K)
   { 
     case '0'://Tecla presionada = al caracter
     PORTC=(DISPLAY[0]);break;//Muestre en el display el numero cero
     case '1':
     PORTC=(DISPLAY[1]);break;
     case '2':
     PORTC=(DISPLAY[2]);break;
     case '3':
     PORTC=(DISPLAY[3]);break;
     case '4':
     PORTC=(DISPLAY[4]);break;
     case '5':
     PORTC=(DISPLAY[5]);break;
     case '6':
     PORTC=(DISPLAY[6]);break;
     case '7':
     PORTC=(DISPLAY[7]);break;
     case '8':
     PORTC=(DISPLAY[8]);break;
     case '9':
     PORTC=(DISPLAY[9]);break;
   }
 }
}
