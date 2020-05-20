#include "gassp72.h"
extern void timer_callback(void);
extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;

typedef struct {
int position;		// 0
int taille;		// 4
void * son;		// 8
int resolution;		// 12
int periode_ticks;	// 16
} type_etat;

type_etat etat;

int PeriodeSon_tick=6552;
int Periode_PWM_Tck=65520;

int main(void){
	
	// activation de la PLL qui multiplie la fr�quence du quartz par 9
			CLOCK_Configure();
			// config port PB1 pour �tre utilis� en sortie
			//GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		// config port PB0 pour �tre utilis� par TIM3-CH3
			GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
// config TIM3-CH3 en mode PWM
	//(72*10^6)/10989
			
			etat.taille=LongueurSon;
			etat.son=&Son;
		  etat.position=0;
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
	

while	(1)
	{
	}
}
