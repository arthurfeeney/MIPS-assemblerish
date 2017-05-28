#
# "starter" program -- might be useful in testing code fragments in (x)spim
#
        #.text
        #.globl  main
main:
#
# opening linkage (save return address)
#
        addi    $sp, $sp, -4
        sw      $ra, 0($sp)
#
# put code to assign initial values to registers here
# examples:
        addi    $s0, $zero, 10          # sets $s0 to 10
        la      $s1, A                  # sets $s1 to address of A
#
# put code to test here
# example:
        sw      $s0, 0($s1)             # stores 10 in A[0]
#
# closing linkage (get return address and restore stack pointer)
#
        lw      $ra, 0($sp)
        addi    $sp, $sp, 4
        jr      $ra
#        .end    main
#
# area for variables and constants
#
# example:
        .data
A:      .word   0, 0, 0, 0              # defines the equivalent of
		 								# "int A[4]"
