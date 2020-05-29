	thumb
	area  moncode, code, readonly
	export reel_imag
;
reel_imag proc
;somme de i allant de 0 a N-1, de xi * cos(ik2pi/N)
;3 args entree: valeur de k, valeur deb tab cos/sin, val deb tab signal
; r0 contient signal, r1 contient k, r2 contient tab cos sin
	push {r5,r8}
; r12 correspond a l'iterateur boucle for 
; r3 contient res
	mov r12,#0 
	mov r8, #0
boucle	
	mul r3,r12,r1
; i*k dans r3
	and r3, #63
;modulo avec N dans r3 (-> index du cos)
	ldrsh r3, [r2,r3, lsl #1]
	ldrsh  r5, [r0, r12, lsl #1]
	mul r3, r5
	add r8, r3
	add r12,#1
	cmp r12, #64
	blt boucle
	mov r0, r8
	pop {r8,r5}
	bx lr
	endp

	end
		

		