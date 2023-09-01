#include <16F88.h>
#device adc=10

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES PUT                   	//Power Up Timer
#FUSES INTRC_IO              	//Internal RC Osc, no CLKOUT
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES PROTECT               	//Code protected from reads

#use delay(int=8000000)

#use rs232(baud=9600,parity=N,xmit=PIN_B5,rcv=PIN_B2,bits=8,stream=PORT1,errors)

