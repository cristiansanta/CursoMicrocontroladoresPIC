#INCLUDE <16F887.h>
#DEVICE ADC=10
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP
#USE RS232(UART1,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#INCLUDE <LCD.C>

//Direcciones de memoria
#BYTE PORTA= 5
#BYTE PORTB= 6
#BYTE PORTC= 7
#BYTE PORTD= 8

long cont=0;
int16 duty=0;
int Timer2,poscaler;
double RPM;
//INTERRUPCION POR RB0
#INT_EXT
void ext_isr()
{
   cont++;
}

void main()
{
 SET_TRIS_A(0x01);//RA0 COMO ENTRADA
 SET_TRIS_B(0x01);//RB0 COMO ENTRADA
 SET_TRIS_D(0);//PUERTO D COMO SALIDA TODOS EN CERO para la LCD
 //CONFIGURAR ENTRADA ANALOGA
 setup_adc_ports(sAN0);//Configura ADC(Lectura analoga de POT)
 setup_adc(adc_clock_internal);//Reloj interno para la conversion
 
 //---------------------------------------------------------------------> CONFIGURACIÓN PWM
 Timer2=249; //Se carga Timer2 con 249
 //Para prescaler se coloca t2_div_by_4
 poscaler=1;//preescaler solo toma valores de 1
 setup_Timer_2(t2_div_by_4,Timer2,poscaler);//Configuracion de Timer
 setup_ccp1(ccp_pwm);//Configurar modulo ccp1 en modo
 
 //Habilitar las interrupciones
 enable_interrupts(int_ext);//Activa interrupcion por RB0
 ext_int_edge(L_TO_H);     //Activa interrupcion por flanco de bajada
 enable_interrupts(global);//Activa interrupciones de forma global
 
 lcd_init();
 lcd_gotoxy(1,1);
 LCD_PUTC("VELOCIDAD MOTOR");
 
 //Hacer infinitamente
 while(true)
 { //Lectura potenciometro
  set_adc_channel(0);//Lee lo que hay en el canal analogo
  delay_us(100);//Espera para la lectura
  duty=read_adc();//Almacena en duty lo que lee del canal 0
  set_pwm1_duty(duty);//duty se aplica a la salida PWM RC2 //01 bits=1023 y 8 bits=255
  
  //Se detiene el programa por un segundo y cuando deja pasar a la siguiente linea de codigo hace el calculo RPM=cont*60/24; para determinar cuantos flancos de bajada hubieron
  delay_ms(969);//Espera por un segundo se pone 999 para corregir el tiempo que gasta en las instrucciones de arriba
  
  RPM=cont*60/24;
  cont=0;//Reinicia el contador de pulsos
  //Visualiza velocidad
  lcd_gotoxy(1,2);
  printf(lcd_putc,"RPM: %f  ",RPM);
  if(RPM>=181)
  printf("M");
 }
}
