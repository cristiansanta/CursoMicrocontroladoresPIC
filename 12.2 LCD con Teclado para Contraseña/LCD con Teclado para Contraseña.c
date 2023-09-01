#include<16f887.h>
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,NOPUT,NOLVP //ORDENES PARA EL PROGRAMADOR
#use delay(clock=4000000)
//#USE RS232(UART1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#define use_portb_kbd TRUE
#define use_portb_lcd TRUE

#include <lcd.c>
#include <kbd.c>

#BYTE PORTC= 7//Direccion de memoria puerto C
//BAUTIZAR PINES
#DEFINE l1 PORTC,0
#DEFINE l2 PORTC,1
#DEFINE l3 PORTC,2
#DEFINE l4 PORTC,3
#DEFINE l5 PORTC,4
#DEFINE l6 PORTC,5
#DEFINE l7 PORTC,6
#DEFINE l8 PORTC,7

//#DEFINE INC PORTC, 0//Bautizar PIN RC0 como INC
//#DEFINE DEC PORTC, 1//Bautizar PIN RC1 como DEC
//#DEFINE START PORTC,2//Bautizar PIN RC2 como START
//ACTVAR RESISTENCIAS PULLUP
//#BYTE WPUB= 0X95// DECLARA REGISTRO OPTION
//#BYTE OPTION_REG = 0X81


void main()
{ int flag=0; char K, password[4]={'1','0','2','8'};//Codigo Secreto
  int m=0;
     LCD_INIT();
     KBD_INIT();
     // OPTION_REG=0;//DESACTIVAR EN EL MAIN EL REGISTRO OPTION
     // WPUB=0b11111111;//seleccionar las PULLUPS a utilizar
    // SET_TRIS_C(0x00);//PONER PUERTO C COMO SALIDA
     port_b_pullups(0xFF); //PIC16F887//Puerto B como entrada.
    //port_b_pullups(TRUE); //PIC16F877A
     set_tris_c(0b00000000);
     portc=0;//comienzan apagados los pines del puerto C
     LCD_PUTC("\f");
 while(true){   
     int i=0, n=0;
    FOR(int DIR=6;DIR<=10;DIR++)//ESTA MISMA VARIABLE DEL CICLO ME SIRVE PARA IR PONIENDO EL CURSOR PARA LA CONTRASEŅA DONDE APARECEN LOS ASTERISCOS
    { 
                 if(flag==0)
                  {
                    lcd_gotoxy(1,1);
                    lcd_putc("DIGITE CLAVE: ");//MENSAJE INICIAL
                  }
                  if(flag==1)
                  {
                    lcd_gotoxy(1,1);
                    lcd_putc("DIGITE DE NUEVO: ");//------------->SI SE HA INGRESADO LA CLAVE INCORRECTA SALE ESTE MENSAJE Y CUANDO INGRESE LA CORRECTA SALE EL MENSAJE DE ARRIBA
                  }
     K=kbd_getc();
     WHILE((k=='\0'))
     {
      K=kbd_getc();      
     }
 if(m<=3 || K=='#'){ ++m;        
     if(K)///////////////////////////////////////////////// DETECTA LA ACTIVACION DEL TECLADO
     { 
       lcd_gotoxy(DIR,2);//----------------VARIABLE DEL CICLO PARA IR PONIENDO LOS ASTERISCOS CON EL CURSOR
       lcd_putc('*');
       n++;//---------------------------->GUARDIAN, LLEVA EL CONTEO, SI SE PASA DE 5 DIGITOS CLAVE INCORRECTA
       if(K==password[i])
       {
         ++i;//-------------------------->GUARDIAN-2 LLEVA EL CONTEO, SI LLEGA A 4 CONTEOS ES PORQUE LA CLAVE ES CORRECTA
         K='\0';
       }
       if((i==4) && (K=='#'))
       { 
               lcd_putc("\f");
               lcd_gotoxy(2,2);
               lcd_putc("CLAVE CORRECTA");
                   for(int j=0;j<=10;j++)
                   {    int C=1;
                         for(int i=0;i<=7;i++)//---------------INICIA SECUENCIA
                                   {
                                     OUTPUT_C(C);
                                     DELAY_MS(35);  
                                     C*=2;
                                   }
                           C=128;
                               for(int i=0;i<=7;i++)
                                  {
                                    OUTPUT_C(C);
                                    DELAY_MS(35);  
                                    C/=2;} 
                           C=1;
                   }//--------------------------------------//TERMINA SECUENCIA
          portc=0;
          DIR=0;
          m=0;
               n=0;//___________________INICIALIZAR VARIABLES
               i=0;
               K='\0';
               lcd_putc("\f");
               flag=0;
       }       
       if((i!=4) && (K=='#')){
               lcd_putc("\f");
               lcd_gotoxy(1,2);
               lcd_putc("CLAVE INCORRECTA");
               BIT_SET(l3);
               delay_ms(1000);
               BIT_CLEAR(l3);
               delay_ms(1000);
               lcd_putc("\f");
               m=0;
               DIR=0;
               n=0;//___________________INICIALIZAR VARIABLES
               i=0;
               K='\0';
               flag=1;
       }
     }
    }
   }
  }
}
  


