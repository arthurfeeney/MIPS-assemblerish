
#
# Test for the interpreter.
#
		.text

		addi	$t2, $zero, 2
		add 	$t3, $zero, $t2
		add		$t4, $t3, $t2
		sub		$t5, $t2, $t4

		.data
A: 		.word 	1, 2, 3, 4		# defines equivalent of int A[4]
