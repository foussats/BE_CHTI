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

		ldr		r2, =etat
		ldr 	r0, [r2, #E_POS]
		ldr 	r1, [r2, #E_TAI]
		cmp 	r0,r1
		blt		cond
		
	; silence ;
		push	{r4,r5}
		mov 	r4, #3
		ldr 	r5, =TIM3_CCR3
		str 	r4,[r5]
		pop		{r4,r5}
		bx		lr
	
	; bruit ;
		; dans r3, valeur du son
cond	ldr		r3,[r2, #E_SON]
		ldrsh 	r3,[r3,r0, LSL #1]
		push 	{r4,r5,r6,r7}
		;+b
		add		r3,#32768
		
		;1/65536 fait 0,0000153 
		ldr		r6,[r2, #E_RES]
		mov		r7,#65536
		mul 	r3, r6
		udiv 	r3, r7
		
		
		ldr 	r7, =TIM3_CCR3
		str 	r3, [r7]
		
		add 	r0, #1
		str		r0, [r2, #E_POS]
		
		pop 	{r7, r6, r5, r4}
		bx 		lr
		
		endp	
		end
 N.B. le registre BSRR est write-only, on ne peut pas le relire

