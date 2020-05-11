		thumb
		area moncode, code, readonly
			
GPIOB_BSRR	equ		0x40010C10	; Bit Set/Reset register
	
		export timer_callback
		
timer_callback proc
		mov		r0, #0
		ldr		r3, =GPIOB_BSRR
		cmp		r0, #0
		beq		zero
	
	; mise a zero de PB1 ;
		
		mov		r1, #0x00020000
		str		r1, [r3]
		mov 	r1,#0
		str		r1,[r2]
		b		fin

	; mise a 1 de PB1 ;

zero	mov		r1, #0x00000002
		str		r1, [r3]
		mov		r1, #1
		str		r1,[r2]
fin		bx		lr

		endp	
		ALIGN
		end
; N.B. le registre BSRR est write-only, on ne peut pas le relire