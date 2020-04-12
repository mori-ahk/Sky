entry
	addi	r14,r0,topaddr

	% Set frame pointer
	subi	r12,r14,8

	% Setting the address and value of y
	lw 	r1,-8(r14)
	addi	r2,r14,-8
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Saving number 2
	addi	r1,r0,2
	sw 	-4(r12),r1

	% set the frame pointer at its initial position
	addi	r12,r12,8

	% Assigning variable
	lw 	r1,-12(r12)
	lw 	r2,-8(r12)
	sw 	0(r2),r1

	% Set frame pointer
	subi	r12,r14,8

	% Setting the address and value of x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Setting the address and value of y
	lw 	r1,-8(r14)
	addi	r2,r14,-8
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Saving number 2
	addi	r1,r0,2
	sw 	-4(r12),r1

	% set the frame pointer at its initial position
	addi	r12,r12,8
	lw 	r1,-4(r12)
	lw 	r2,-12(r12)

	% multiplying two numbers
	mul	r1,r1,r2
	sw 	-4(r12),r1

	% set the frame pointer at its initial position
	addi	r12,r12,8

	% Assigning variable
	lw 	r1,-12(r12)
	lw 	r2,-8(r12)
	sw 	0(r2),r1

	% Set frame pointer
	subi	r12,r14,8

	% If statement
main_1_if	nop

	% Setting the address and value of y
	lw 	r1,-8(r14)
	addi	r2,r14,-8
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Setting the address and value of x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% set the frame pointer at its initial position
	addi	r12,r12,8

	% Comparing
	cgt	r1,r1,r2
	sw 	-4(r12),r1

	% check condition value
	bz	r1,main_1_if_else

	% Set frame pointer
	subi	r12,r14,8

	% Setting the address and value of x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% Writing variable x
	lw 	r1,-4(r12)
	jl	r15,putint

	% Printing new line
	addi	r1,r0,10
	putc	R1
	j	main_1_if_end
main_1_if_else	nop

	% Set frame pointer
	subi	r12,r14,8

	% Setting the address and value of y
	lw 	r1,-8(r14)
	addi	r2,r14,-8
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% Writing variable y
	lw 	r1,-4(r12)
	jl	r15,putint

	% Printing new line
	addi	r1,r0,10
	putc	R1
main_1_if_end	nop

	% Set frame pointer
	subi	r12,r14,8

	% Setting the address and value of x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% Writing variable x
	lw 	r1,-4(r12)
	jl	r15,putint

	% Printing new line
	addi	r1,r0,10
	putc	R1
hlt
