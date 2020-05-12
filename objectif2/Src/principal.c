#include "gassp72.h"
#include <stdio.h>
#include <stdlib.h>

#define M2TIR 985661

//#define M2TIR 10000
int var = 0;
int SYSTICK_PER = 5*72000;
unsigned short *dma_buf;
int N = 64;
int occurence[6];
int valeurk[6] = {17, 18, 19, 20, 23, 24};
int score[6];
int tab_res[6];


//extern int TabSin;
//extern int TabCos;
extern int dft(unsigned short *sig, int k);
//extern short TabSigMine;
//extern short TabSig;
//extern short TabSig1;
//extern short TabSig2;

void sys_callback(void){


	// Démarrage DMA pour 64 points
	//GPIO_Set(GPIOB, 1);
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(int i = 0; i<6; i++){
		int k = valeurk[i];
		tab_res[i] = dft(dma_buf, k);
		if(tab_res[i] > M2TIR){
			occurence[i]++;
		}else{
			if(occurence[i]>=3){
				score[i]++;
			}
			occurence[i] = 0;
		}
	}
}




 int main(void){
	 
	 dma_buf = malloc(N*sizeof(short));

	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 0x33 );
	Single_Channel_ADC( ADC1, 2 );
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1( 0, dma_buf );

	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff( SYSTICK_PER );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;
	//free(dma_buf);
	while	(1)
		{
		}
}
 


	
	//GPIO_Clear(GPIOB, 1);

