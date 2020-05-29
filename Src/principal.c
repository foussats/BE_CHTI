#include "gassp72.h"
#include <stdio.h>
#include <stdlib.h> 
extern void timer_callback(void);
extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;

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

typedef struct {
int position;		// 0
int taille;		// 4
void * son;		// 8
int resolution;		// 12
int periode_ticks;	// 16
} type_etat;

type_etat etat;

void sys_callback(void){


	// D�marrage DMA pour 64 points
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
				etat.position=0;
			}
			occurence[i] = 0;
		}
	}
}



int PeriodeSon_tick=6552;
int Periode_PWM_Tck=655;

int main(void){
		 dma_buf = malloc(N*sizeof(short));

	// activation de la PLL qui multiplie la fr�quence du quartz par 9
			CLOCK_Configure();
			// config port PB1 pour �tre utilis� en sortie
			//GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		// config port PB0 pour �tre utilis� par TIM3-CH3
		GPIO_Configure(GPIOA, 2, INPUT, ANALOG);

			GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
// config TIM3-CH3 en mode PWM
	//(72*10^6)/10989
			
			etat.taille=LongueurSon;
			etat.son=&Son;
		  etat.position=LongueurSon;
			etat.resolution = PWM_Init_ff( TIM3, 3, Periode_PWM_Tck );

			
			// initialisation du timer 4
			// Periode_en_Tck doit fournir la dur�e entre interruptions,
			// exprim�e en p�riodes Tck de l'horloge principale du STM32 (72 MHz)
			Timer_1234_Init_ff( TIM4, PeriodeSon_tick);
			// enregistrement de la fonction de traitement de l'interruption timer
			// ici le 2 est la priorit�, timer_callback est l'adresse de cette fonction, a cr��r en asm,
			// cette fonction doit �tre conforme � l'AAPCS
			Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
			// lancement du timer
			Run_Timer( TIM4 );
	
			// activation ADC, sampling time 1us
			Init_TimingADC_ActiveADC_ff( ADC1, 0x33 );
			Single_Channel_ADC( ADC1, 2 );
			// D�clenchement ADC par timer2, periode (72MHz/320kHz)ticks
			Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
			// Config DMA pour utilisation du buffer dma_buf (a cr��r)
			Init_ADC1_DMA1( 0, dma_buf );

			// Config Timer, p�riode exprim�e en p�riodes horloge CPU (72 MHz)
			Systick_Period_ff( SYSTICK_PER );
			// enregistrement de la fonction de traitement de l'interruption timer
			// ici le 3 est la priorit�, sys_callback est l'adresse de cette fonction, a cr��r en C
			Systick_Prio_IT( 3, sys_callback );
			SysTick_On;
			SysTick_Enable_IT;
			//free(dma_buf);

while	(1)
	{
	}
}
