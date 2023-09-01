#include<16f887.h>
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,NOPUT,NOLVP //ORDENES PARA EL PROGRAMADOR
#use delay(clock=4000000)

#define use_portb_kbd TRUE
#define use_portb_lcd TRUE

#include <lcd.c>
#include <kbd.c>

//#BYTE PORTC= 7//Direccion de memoria puerto C
//#DEFINE INC PORTC, 0//Bautizar PIN RC0 como INC
//#DEFINE DEC PORTC, 1//Bautizar PIN RC1 como DEC
//#DEFINE START PORTC,2//Bautizar PIN RC2 como START
//ACTVAR RESISTENCIAS PULLUP
//#BYTE WPUB= 0X95// DECLARA REGISTRO OPTION
//#BYTE OPTION_REG = 0X81
char K;
int DIR;

void main()
{
  LCD_INIT();
  KBD_INIT();
  // OPTION_REG=0;//DESACTIVAR EN EL MAIN EL REGISTRO OPTION
  // WPUB=0b11111111;//seleccionar las PULLUPS a utilizar
  // SET_TRIS_C(255);//PONER PUERTO C COMO SALIDA
  port_b_pullups(0xFF); //PIC16F887
 //port_b_pullups(TRUE); //PIC16F877A

  lcd_putc("\f");//Limpia LCD
  while(true)
  {
    DIR=0;
    LCD_PUTC("\f");
    while(DIR<17)
    {
     K=kbd_getc();
     
     WHILE((k=='\0'))
     {
      K=kbd_getc();      
     }
     if((K!='*') && (K!='#'))
     {
       lcd_putc(K);
       DIR++;
     }
    }
  }
}
