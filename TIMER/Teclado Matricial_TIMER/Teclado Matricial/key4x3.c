/////////////////////////////////////////////////////////////////////////// 
////                             Flex_KBD.C                            //// 
////                  Generic keypad scan driver                       //// 
////                                                                   //// 
////  kbd_init()   Must be called before any other function.           //// 
////                                                                   //// 
////  c = kbd_getc(c)  Will return a key value if pressed or /0 if not //// 
////                   This function should be called frequently so as //// 
////                   not to miss a key press.                        //// 
////                                                                   //// 
/////////////////////////////////////////////////////////////////////////// 


#byte  status = getenv("SFR:STATUS")
#bit RP0=GETENV("BIT:RP0")
#bit RP1=GETENV("BIT:RP1")


 



//Keypad connection:  

//#define col0 PIN_B4   // Obligatorio para procesar por interrupcion
//#define col1 PIN_B5   // Obligatorio para procesar por interrupcion
//#define col2 PIN_B6  // Obligatorio para procesar por interrupcion
//#define row0 PIN_E0  // pin opcional, elegir cualquiera
//#define row1 PIN_C2  // pin opcional, elegir cualquiera
//#define row2 PIN_C1  // pin opcional, elegir cualquiera
//#define row3 PIN_E2  // pin opcional, elegir cualquiera

// Keypad layout: 
char const KEYS[4][3] = {{'1','2','3'}, 
                         {'4','5','6'}, 
                         {'7','8','9'}, 
                         {'*','0','#'}}; 



void kbd_init() {    
     input(col0);
     input(col1);
     input(col2);
     output_low(row0);
     output_low(row1);
     output_low(row2);
     output_low(row3); 
     port_b_pullups(TRUE); // habilita pull up 
     enable_interrupts(INT_RB);// Habilita interrupcion Rb4-Rb7
} 

short int kbd_Presionado (void) 
{ 
   if (input (col0) & input (col1) & input (col2) ) 
      return (0);  //  no presionado
   else 
      return (1);  // teclas presionada
}

char kbd_getc( ) { 
   static byte row,col; 
   char kchar;
   kchar=0; // Retorna 0 si no no hay presionada   
   col =10; // sino encuentra
   
   for(row=0;row<=4;row++) { // inicia escaneo de filas
   
       switch (row) { 
         case 0  : 
               output_low(row0);
               output_high(row1); 
               output_high(row2); 
               output_high(row3);
                    break; 
         case 1   : 
               output_high(row0);
               output_low(row1); 
               output_high(row2); 
               output_high(row3); 
                    break; 
         case 2   : 
               output_high(row0);
               output_high(row1); 
               output_low(row2); 
               output_high(row3); 
                    break; 
         case 3   : 
               output_high(row0);
               output_high(row1); 
               output_high(row2); 
               output_low(row3); 
                    break;            
       } 

      //------------- verifica columna presionada
        
             if(!input (col0)) {
                col=0; //tecla encpntrada en columna 0
                break; 
             }else if(!input (col1)) {
                col=1; //tecla encpntrada en columna 1
                break; 
             }else if(!input (col2)) {
                col=2; //tecla encpntrada en columna 2
                break; 
             }           
           
   } 
   
    kbd_init(); // espera proxima tecla
   if (col!=10){ kchar =KEYS[row][col]; }
  return kchar; 
}
