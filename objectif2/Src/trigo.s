	thumb
	area  moncode, code, readonly
	extern TabSin
	extern TabCos
	export somme
;
somme proc
	mov r1,r0
;on prend le cos dans le tab
	ldr r2, =TabCos
	ldrsh r0, [r2,r0, lsl #1]
; on le met au carré
	mul r0,r0,r0
; dans une autre var on va chercher le sin
	ldr r3, =TabSin
	ldrsh r1, [r3,r1, lsl #1]
; on le met au carre
	mul r1,r1,r1
; on add le cos et le sin
	add	r0,r1
	bx lr
	
	endp
	end
		

		