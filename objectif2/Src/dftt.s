	thumb
	area moncode, code,READONLY
	extern TabSig2
	extern TabSin
	extern TabCos
	extern reel_imag
	export dft
		
dft proc
;adr de base signal et valeur de k
;signal dans r0 et k dans r1
	push {lr,r4,r6,r7}
	
	ldr r2, =TabCos
	mov r4,r0
	bl reel_imag
; res du reel dans r6 et mise au carré
	smlal r6,r7,r0,r0
	
	ldr r2, =TabSin
	mov r0,r4
	bl reel_imag
;res de la partie imaginaire dans r0 et mise au carré
	smlal r6,r7,r0,r0
	
	mov r0, r7
	
	pop{r7,r6,r4,pc}
	bx lr
	endp
		
	end