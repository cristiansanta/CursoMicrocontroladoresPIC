#INCLUDE <16F887.h>
//#USE DELAY(CLOCK=4000000) //RELOJ INTERNO 4MHz
#device ADC=10
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP
#USE DELAY(CLOCK=4000000,crystal)//Crystal Externo 4MHz
#USE RS232(UART1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#include <LCD.C>
#DEFINE USE_PORTB_KBD //Por defecto el teclado se conecta al puerto D
#INCLUDE <kbd4x4_1.C>

#USE standard_io(b)//Definir el puerto B como estandar de entradas y salidas
#DEFINE Key_wait 200//Tiempo de espera del teclado en milisegundos - si en 200ms no presionan nada continue con la siguiente linea del programa

#BYTE PORTA= 5//Entrada Sensor
#BYTE PORTC= 7//Salida PWM
#BYTE PORTB= 6//Teclado entrada
#BYTE PORTD= 8 //SALIDA Para la LCD
//Variables configuracion PWM
long bits;//Almacena los bits
float temp;//Almacena temperatura

   int DIR;//Contar digitos que se van mostrando en la LCD

//FUNCION TECLA
char tecla(void)
{
   char k;
   do{ //espera hasta que se presione una tecla
       k=kbd_getc();//Captura la informacion obtenida del teclado
     }
    while(k=='\0');
    return(k);    
}

/*===========================================================================*/
/*=========================    FUNCION TECLA CON TIMER    ===================*/
/*===========================================================================*/
/*PREGUNTA POR UNA TECLA POR U TIEMPO DETERMINADO Y SI NO HAY ACTIVIDAD, DEJA DE
PREGUNTAR Y DEJA QUE EL PIC CONTINUE CON SU TRABAJO*/
CHAr tecla_time(void)//tipo interrupcion las demas lineas de codigo se pueden seguir ejecutando pero si se detecta el teclado muestra el valor retornado
{
   char c='\0';
   unsigned int16 timeout;
   timeout=0;
   c=kbd_getc();//Captura valor del teclado
   while(c=='\0' && (++timeout < 20000))
   {
     delay_us(10);//Incrementa cada 10 microseconds//////OTRA OPCION DE INTERRUPCIÓN
     c=kbd_getc();//Captura valor del teclado
   }
   return (c);
}

void main()
{ 
  char k_1;
       //PORT_B_PULLUPS(TRUE);//PARA EL 16F887 NO SIRVE ESTA INSTRUCCION //Habilitar resistencias internas de los 1ros 4 puertos de RB
       port_b_pullups(0xFF);//Utiliza resistencias internas PULLUP DEL PUERTO B
      //! OPTION_REG = 0;//En el main se desactiva el registro OPTION
      //! WPUB=0B11111111;// y se seleccionan los PULLUPS que se van a utilizar 
       set_tris_a(0b00000001);//RA0 COMO ENTRADA
      // SET_TRIS_A(0x01);//otra forma de declarar pin A0 como entrada
       SET_TRIS_B(0);//SALIDA
       // SET_TRIS_D(0B00000000);//NO SE CONFIGURA PARA LA LCD PORQUQE YA ESTA DECLARADA POR DEFECTO EN LA LIBRERIA
       
       setup_adc_ports(sAN0);//POner RA0 como Analogo
       setup_adc(adc_clock_internal);//SELÉCCIONO RELOJ INTERNO PARA CONVERSIÓN
          
       KBD_INIT();//inicializar DRIVER del teclado
       SET_TRIS_C(0);//Configurar el puerto C como salida IMPORTANT
       LCD_INIT();////inicializar DRIVER de LCD
       LCD_PUTC("\f");//Limpia LCD
       
       while(true)
       { DIR=9;
         lcd_gotoxy(1,2);
         lcd_putc("Mire: ");
         lcd_gotoxy(1,2);
           while(DIR<17)
           {
                       
             if(k_1!='\0'){//Pregunta si K esta vacio o no esta vacio
                LCD_GOTOXY(DIR,2);
                LCD_PUTC(k_1);
                printf("%c",k_1);
                k_1='\0';//Deja vacia la variable
                DIR++;
             }
             //FORMAS DE CAPTURAR DATOS DEL TECLADO
            k_1=tecla_time();//recoge el valor de la funcion tecla_time INTERRUPCION(interna)==Timer
            //k_1=tecla();//recoge el valor de la funcion tecla
           //  k_1=kbd_getc();//recoge el valor directamente de la funcion
             
             if(DIR>16)
             LCD_PUTC("\f");//Limpia LCD 
             
              //Lectura ADC
         set_adc_channel(0); //Selecciono canal RA0
         delay_ms(1);   //Llama retardo 1ms
         bits=read_adc();//Guarda el dato del sensor
         
         temp=bits*0.4882;//conversion de bits a temperatura
         lcd_gotoxy(1,1);//Ubiquese en la posicion 1,1
         printf(lcd_putc,"Temperatura: %f ",temp);//Muestra el valor numerico de la conversion

         } 
      }
}
