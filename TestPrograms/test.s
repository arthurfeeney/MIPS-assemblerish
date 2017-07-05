
#
# Test for the interpreter.
#
		#.text
		#.global main

main:
		addi	$s0, $zero, 10
		addi	$t2, $zero, 11
		add 	$t5, $s0, $t2

		la		$s1, A
        lw      $t0, 0($s1)

        sw      $t0, 4($s1)

        j       label
        addi    $t5, $t5, 420

label:  # skips the addi !!!


        beq     $t5, $t5, 4
qwop:   addi    $t5, $zero, 1


        addiu   $t5, $t5, 2
        addu    $t5, $t5, $t5

        and     $t5, $t5, $t2

        la      $s1, qwop

        #jr      $s1

		.data
A: 		.word 	1, 2, 3, 4		# defines equivalent of int A[4]
