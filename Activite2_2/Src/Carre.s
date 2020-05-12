		thumb
		area moncode, code, readonly
		export timer_callback
	
GPIOB_BSRR	equ		0x40010C10	; Bit Set/Reset register
	
		extern var
		
		
timer_callback proc
		ldr		r2, =var
		ldr		r0, [r2]
		cbz 	r0, zero
		
	; mise a zero de PB1 ;
		ldr		r3, =GPIOB_BSRR
		mov		r1, #0x00020000
		str		r1, [r3]
		mov 	r1,#0
		str		r1,[r2]
		bx		lr
		
	; mise a 1 de PB1 ;
	ALIGN
zero	ldr		r3, =GPIOB_BSRR
		mov		r1, #0x00000002
		str		r1, [r3]
		mov		r1, #1
		str		r1,[r2]
		bx		lr
	
		endp	
		end
; N.B. le registre BSRR est write-only, on ne peut pas le relire