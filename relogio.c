/* Autores Sandro e David
 * Created:   sex abr 5 2019
 * Processor: PIC18F4520
 * Compiler:  MPLAB XC8
 */
  
#include <xc.h>
#define _XTAL_FREQ 16000000		// informa ao compilador a freq de clock
				       //informação usada nas funções de delay.

unsigned char su=0;				// variável global do contador

void __interrupt() TrataInt (void){	//tratamento de interrupção do timer zero
    su++;				// incrementa contador (unidade de segundo)
    TMR0H = 0x0B;		// valor obtido pela fórmula A=(t*f)/(4*prescaler)
    TMR0L = 0xDC;		//2^b-A = ao valor que vai em TMR0H e TMR0L
    INTCONbits.TMR0IF = 0;		// zera flag do estouro do timer
				        // se não zerar o programa para.
   
}


void main(void) {			
    TRISD = 0x00;
    TRISB = 0x00;
   
    T0CON = 0x95;	//configrações abaixo
   /* T08BIT = 0, configura timer para 16 bits
   ** T0CS = 0, configura para usar freq/4 (frequencia interna)
   ** PSA = 0, prescaler atribuído.
   ** prescaler de 64 
   */
    INTCONbits.INT0IE = 1;	// configuração para tratamento
    INTCONbits.GIE = 1;		// de interrupção sem ordem de prioridade.
    INTCONbits.TMR0IE = 1;      // Habilita interrupções timer 0
    TMR0H = 0x0B;		// valor obtido pela fórmula A=(t*f)/(4*prescaler)
    TMR0L = 0xDC;		//2^b-A = ao valor que vai em TMR0H e TMR0L
   
    
    char numeros[10];			//vetor com os acendimentos para display
    numeros[0]=0x03F;			// de 7 segmentos.
    numeros[1]=0x06;
    numeros[2]=0x5B;
    numeros[3]=0x4F;       
    numeros[4]=0x66;
    numeros[5]=0x6D;
    numeros[6]=0x7D;
    numeros[7]=0x07;
    numeros[8]=0x7F;
    numeros[9]=0x6F;				
    unsigned char sd = 0, mu = 0, md = 0;	//dezena de segundo, unidade de minuto e dezena de minuto.
						// usado o char para economizar memória
    while(1){
					
	      		
	      PORTB = 0b10000000;	
	      PORTD = numeros[su]; 	
	      __delay_ms (5);
	      
	      
	      PORTB = 0b01000000; 
	      PORTD = numeros[sd];
          __delay_ms (5);
       
	       
	      PORTB = 0b00100000;
	      PORTD = numeros[mu];
          if(su%2==0){
	      PORTDbits.RD7 = 1;
          }// ponto dividindo minutos e segundos.
	     __delay_ms (5);
         
	     PORTB = 0b00010000;
	     PORTD = numeros[md];
         __delay_ms (5);
         
	
	 if(su>=10){
	    su = 0;
	    sd++;
	
		  if(sd>=6){
		  sd = 0;
		  mu++;
		       
			if(mu>=10){
			mu = 0;
			md++;
	 
	 
			     if(md >= 6){
			     md = 0;
	}}}}
    }
    return;
}