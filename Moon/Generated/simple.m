entry
	addi	r14,r0,topaddr

	% Writing variable x
	lw 	r1,-4(r14)
	jl	r15,putint
hlt
