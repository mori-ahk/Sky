factorial_0	nop

	% Saving values of reserved registers
	sw 	-4(r12),r15
	sw 	-8(r12),r14
	sw 	-12(r12),r12

	% Moving stack pointer to the same address as frame pointer
	subi	r14,r12,12

	% Set frame pointer
	subi	r12,r14,4

	% If statement
if_1	nop

	% Allocating memory for variable x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Saving number 1
	addi	r1,r0,1
	sw 	-4(r12),r1

	% set the frame pointer at its initial position
	addi	r12,r12,8
	lw 	r1,-4(r12)
	lw 	r2,-12(r12)

	% Comparing
	ceq	r1,r1,r2
	sw 	-4(r12),r1

	% check condition value
	bz	r1,if_1_else

	% Set frame pointer
	subi	r12,r14,4

	% Saving number 1
	addi	r1,r0,1
	sw 	-4(r12),r1

	% Returning from function factorial
	add	r13,r12,r0
	j	factorial_0_end
	j	if_1_end
if_1_else	nop

	% Set frame pointer
	subi	r12,r14,4

	% Allocating memory for function call factorial

	% Moving frame pointer to reserve stack space for current scope
	subi	r12,r12,12

	% Allocating memory for function params

	% Allocating memory for variable x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Saving number 1
	addi	r1,r0,1
	sw 	-4(r12),r1

	% set the frame pointer at its initial position
	addi	r12,r12,8
	lw 	r1,-4(r12)
	lw 	r2,-12(r12)

	% Adding two number
	sub	r1,r1,r2
	sw 	-4(r12),r1
	subi	r12,r12,4

	% Move back the frame pointer to first of the function stack frame
	addi	r12,r12,4

	% Moving back the frame pointer to its position before the function call
	addi	r12,r12,12
	jl	r15,factorial_0

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Allocating memory for variable x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% set the frame pointer at its initial position
	addi	r12,r12,8
	lw 	r1,-4(r12)
	lw 	r2,-12(r12)

	% multiplying two numbers
	mul	r1,r1,r2
	sw 	-4(r12),r1

	% Returning from function factorial
	add	r13,r12,r0
	j	factorial_0_end
if_1_end	nop
factorial_0_end	nop

	% Moving stack pointer back to its position before function definition
	addi	r12,r14,12

	% setting values of reserved registers to their old values before function definition
	lw 	r15,-4(r12)
	lw 	r14,-8(r12)
	lw 	r12,-12(r12)

	% Loading return value to r1
	lw 	r1,-4(r13)
	sw 	-4(r12),r1
	jr	r15
add_0	nop

	% Saving values of reserved registers
	sw 	-4(r12),r15
	sw 	-8(r12),r14
	sw 	-12(r12),r12

	% Moving stack pointer to the same address as frame pointer
	subi	r14,r12,12

	% Set frame pointer
	subi	r12,r14,4

	% Allocating memory for variable x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
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

	% Adding two number
	add	r1,r1,r2
	sw 	-4(r12),r1

	% Returning from function add
	add	r13,r12,r0
	j	add_0_end
add_0_end	nop

	% Moving stack pointer back to its position before function definition
	addi	r12,r14,12

	% setting values of reserved registers to their old values before function definition
	lw 	r15,-4(r12)
	lw 	r14,-8(r12)
	lw 	r12,-12(r12)

	% Loading return value to r1
	lw 	r1,-4(r13)
	sw 	-4(r12),r1
	jr	r15
print_0	nop

	% Saving values of reserved registers
	sw 	-4(r12),r15
	sw 	-8(r12),r14
	sw 	-12(r12),r12

	% Moving stack pointer to the same address as frame pointer
	subi	r14,r12,12

	% Set frame pointer
	subi	r12,r14,8

	% Allocating memory for variable x
	lw 	r1,-4(r14)
	addi	r2,r14,-4
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% moving frame pointer 8 byte up
	addi	r12,r12,-8

	% Allocating memory for variable y
	lw 	r1,-8(r14)
	addi	r2,r14,-8
	sw 	-4(r12),r1
	sw 	-8(r12),r2

	% set the frame pointer at its initial position
	addi	r12,r12,8
	lw 	r1,-4(r12)
	lw 	r2,-12(r12)

	% Adding two number
	add	r1,r1,r2
	sw 	-4(r12),r1

	% Returning from function print
	add	r13,r12,r0
	j	print_0_end
print_0_end	nop

	% Moving stack pointer back to its position before function definition
	addi	r12,r14,12

	% setting values of reserved registers to their old values before function definition
	lw 	r15,-4(r12)
	lw 	r14,-8(r12)
	lw 	r12,-12(r12)

	% Loading return value to r1
	lw 	r1,-4(r13)
	sw 	-4(r12),r1
	jr	r15
entry
	addi	r14,r0,topaddr
main	nop

	% Set frame pointer
	subi	r12,r14,8

	% Allocating memory for function call print

	% Moving frame pointer to reserve stack space for current scope
	subi	r12,r12,12

	% Allocating memory for function params

	% Allocating memory for function call add

	% Moving frame pointer to reserve stack space for current scope
	subi	r12,r12,12

	% Allocating memory for function params

	% Allocating memory for function call factorial

	% Moving frame pointer to reserve stack space for current scope
	subi	r12,r12,12

	% Allocating memory for function params

	% Saving number 4
	addi	r1,r0,4
	sw 	-4(r12),r1
	subi	r12,r12,4

	% Move back the frame pointer to first of the function stack frame
	addi	r12,r12,4

	% Moving back the frame pointer to its position before the function call
	addi	r12,r12,12
	jl	r15,factorial_0
	subi	r12,r12,4

	% Move back the frame pointer to first of the function stack frame
	addi	r12,r12,4

	% Moving back the frame pointer to its position before the function call
	addi	r12,r12,12
	jl	r15,add_0
	subi	r12,r12,4

	% Allocating memory for function call add

	% Moving frame pointer to reserve stack space for current scope
	subi	r12,r12,12

	% Allocating memory for function params

	% Allocating memory for function call factorial

	% Moving frame pointer to reserve stack space for current scope
	subi	r12,r12,12

	% Allocating memory for function params

	% Saving number 5
	addi	r1,r0,5
	sw 	-4(r12),r1
	subi	r12,r12,4

	% Move back the frame pointer to first of the function stack frame
	addi	r12,r12,4

	% Moving back the frame pointer to its position before the function call
	addi	r12,r12,12
	jl	r15,factorial_0
	subi	r12,r12,4

	% Move back the frame pointer to first of the function stack frame
	addi	r12,r12,4

	% Moving back the frame pointer to its position before the function call
	addi	r12,r12,12
	jl	r15,add_0
	subi	r12,r12,4

	% Move back the frame pointer to first of the function stack frame
	addi	r12,r12,8

	% Moving back the frame pointer to its position before the function call
	addi	r12,r12,12
	jl	r15,print_0

	% Writing variable y
	lw 	r1,-4(r12)
	jl	r15,putint

	% Printing new line
	addi	r1,r0,10
	putc	R1
main_end	nop
hlt
