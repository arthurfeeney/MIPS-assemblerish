
#
# Test for the interpreter.
#
		#.text
		#.global main

main:
    	la 		$t1, A
		addiu 	$t1, $t1, 1
		lw		$t2, 0($t1)
		addiu 	$t2, $t2, 79

		addi 	$v0, $zero, 11
		addi 	$a0, $zero, 98
		syscall


		.data
A: 		.word 	1, 5, 3, 4		# defines equivalent of int A[4]
