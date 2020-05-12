#include "gassp72.h"

void timer_callback(void);
int var = 0;
int Periode_en_Tck = 100;

extern int TabSin;
extern int TabCos;
int somme(int);


int main(void){
			int max=0;
			int min=0x40000000;
			int S;
			for (int i=0;i<64; i++){
				S=somme(i);
				if(S>max){
					max=S;
				}
				if(S<min){
					min=S;
				}
			}
			// activation de la PLL qui multiplie la fréquence du quartz par 9
			CLOCK_Configure();
			// config port PB1 pour être utilisé en sortie
			GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
			// initialisation du timer 4
			// Periode_en_Tck doit fournir la durée entre interruptions,
			// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
			Timer_1234_Init_ff( TIM4, Periode_en_Tck );
			// enregistrement de la fonction de traitement de l'interruption timer
			// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
			// cette fonction doit être conforme à l'AAPCS
			Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
			// lancement du timer
			Run_Timer( TIM4 );
while	(1)
	{
	}
}
