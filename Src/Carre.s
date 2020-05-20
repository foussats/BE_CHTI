		thumb
		area moncode, code, readonly
		export timer_callback
GPIOB_BSRR	equ		0x40010C10	; Bit Set/Reset register		
		extern variable
		extern etat
	
E_POS	equ	0
E_TAI	equ	4
E_SON	equ	8
E_RES	equ	12
E_PER	equ	16
		
		
TIM3_CCR3	equ		0x4000043C	; adresse registre PWM
GPIOB_BSRF	equ		0x40010C10	; Bit Set/Reset register
	
timer_callback proc
		;on met l'adresse de la variable etat dans r2
		ldr		r2, =etat
		;on charge la valeur de la variable etat.position dans r0
		ldr 	r0, [r2, #E_POS]
		;on charge la valeur de la variable etat.taille dans r0
		ldr 	r1, [r2, #E_TAI]
		;comparaison de la position et de la taille
		cmp 	r0,r1
		blt		cond
		
	; si po>taille alors emission de silence ;
		push	{r4,r5}
		;on met la valeur 3 dans r4
		mov 	r4, #3
		;on load l'adresse de TIM3_CRR3 dans r5
		ldr 	r5, =TIM3_CCR3
		;on charge la valeur 3 dans la variable TIM3_CRR3
		str 	r4,[r5]
		pop		{r4,r5}
		bx		lr
	
	; si pos<taille alors émission de bruit ;
		; dans r3, valeur de la variable etat.son
cond	ldr		r3,[r2, #E_SON]
		ldrsh 	r3,[r3,r0, LSL #1]
		push 	{r4,r5,r6,r7}
		;ajout composante continue
		add		r3,#32768
		
		;1/65536 fait 0,0000153 
		ldr		r6,[r2, #E_RES]
		mov		r7,#65536
		;on multiplie la résolution par la valeur de la variable etat.son 
		;puis on divise par 65536 pour mettre à l'achelle
		mul 	r3, r6
		udiv 	r3, r7
		
		;on charge la valeur de l'échantillon mise à l'échelle dans TIM3_CRR3
		ldr 	r7, =TIM3_CCR3
		str 	r3, [r7]
		;on incrémente la position pour passer à l'échantillon suivant
		add 	r0, #1
		str		r0, [r2, #E_POS]
		
		pop 	{r7, r6, r5, r4}
		bx 		lr
		
		endp	
		end
 N.B. le registre BSRR est write-only, on ne peut pas le relire

