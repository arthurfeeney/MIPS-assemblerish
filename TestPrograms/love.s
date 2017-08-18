
# adds the positive and negative numbers. 
# proper output should be 0. (!!!)

main:

		la		$s0, A # loads a[0] into s0
		la		$s1, B # loads b[0] into s1

		addi 	$s2, $zero, 0 # the sum of elements.
		addi 	$s3, $zero, 0 # keeps track of the nummber of iterations.
love:

		lw		$t0, 0($s0)
		lw		$t1, 0($s1)
		
		addiu	$s0, $s0, 1
		addiu	$s1, $s1, 1

		add		$s2, $s2, $t0
		add		$s2, $s2, $t1

		addiu 	$s3, $s3, 1
		
		slti	$t2, $s3, 2			#
									# loop while s3 is < 5
		bne 	$t2, $zero, -9		#

		addi 	$v0, $zero, 1
		add 	$a0, $zero, $s2
		syscall

		la		$s4, C

		lw		$t4, 1($s4)

		addi	$v0, $zero, 11
		add 	$a0, $zero, $t4
		syscall

		.data
A: 		.word		1, 2, 3, 4, 5
B: 		.word		-1, -2, -3, -4, -6
C: 		.asciiz 	abc
