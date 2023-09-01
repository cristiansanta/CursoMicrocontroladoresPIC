#include <16f887.h>
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP

Byte CONST display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};//Matriz
#BYTE PORTB= 6//DIRECCION DE MEMORIA
#BYTE PORTC=7//DIRECCION DE MEMORIA
#DEFINE T_UNI PORTC,0//Definicion de variables
#DEFINE T_DEC PORTC,1//Definicion de variables

int cont;
long conta_ret;

void mostrar()            //MULTIPLEXACION
{
  int uni,dec;
  dec=cont/10;//si es 23 coge el 2
  uni=cont%10;//si es 23 coge el 3
   
  PORTB=(display[uni]);  
  BIT_SET(T_UNI);//ENCIENDE EL TRANSISTOR DE UNIDADES
  delay_ms(1);//retatrdo de un milisegundo
  BIT_CLEAR(T_UNI);//APAGA EL PIN DE UNIDADES
  
  PORTB=(display[dec]);//manda a ambos displays pero los 2 estan apagados  
  BIT_SET(T_DEC);//ENCIENDE EL PIN DE DECENAS
  delay_ms(1);//retatrdo de un milisegundo
  BIT_CLEAR(T_DEC);//APAGA EL PIN DE DECENAS
}

void ret_1_seg()//rutina de retardo de 1 segundo, que va llamando en todo momento a multiplexaci�n
{conta_ret=200;//500 //para que de este modo mientras se est� esperando a que el retardo de 1 segundo se cumpla, vaya mostrando el valor del temporizador actual
 while(conta_ret>0)
 { mostrar();
   conta_ret--;
 }
}

void main()
{
 SET_TRIS_B(0);//puesto como salida
 SET_TRIS_C(0);//Puesto como salida
 cont=0;
  WHILE(true)//haga por siempre
  { cont=0;
    while(cont<9999)//100//mientras la variable cont sea menor que 100
    { 
      ret_1_seg();//llama la rutina o funcion
      cont++;// Va incrementando la variable cont
    }
  }
}
