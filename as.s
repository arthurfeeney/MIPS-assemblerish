
#hi there

hi: # yolo
		addi	$t2, $zero, 1 # adds 1 to t2
		add		$t4, $t2, $t3
		sub		$t4, $t2, $t3

word:
		sw		$t1, 0($t2)
		lw		$t1, 0($t2)
		j		hi			# whoed to u home
		j 		word
		beq		$t1, $t2, word
		bne 	$t1, $t2, word # whats up
		addiu	$t1, $t2, 0
		addu	$t1, $t2, $t3
		and		$t1, $t2, $t3
		andi 	$t1, $t2, 2
		jal		word
		lbu 	$t1, 75($t2)
		lhu 	$t1, 75($t2)
		lui		$t1, 1
		ori 	$t1, $t2, 420
		sll		$t1, $t2, 2
		srl 	$t1, $t2, 2
		sra 	$t1, $t2, 2
		subu	$t1, $t2, $t3
swag:	or 		$t1, $t2, $t3
		la 		$t1, word #pseudo command :o
		xor		$t1, $t2, $t3
		nor 		$t1, $t2, $t3
		mult	$t1, $t2
		div 	$t1, $t2
		divu	$t1, $t2
        multu   $t1, $t2
        sllv    $t1, $t2, $t3
        srav    $t1, $t2, $t3
        xori    $t1, $t2, 0
        slt     $t1, $t2, $t3
        sltu     $t1, $t2, $t3
        slti    $t1, $t2, 0
        sltiu   $t1, $t2, 0
        bgtz    $t1, 0
        blez    $t1, 0
        jalr    $t1, $t2
