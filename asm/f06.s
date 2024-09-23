	.file	"f06.cc"
	.text
	.globl	_Z1fPi
	.type	_Z1fPi, @function
_Z1fPi:
	endbr64
	movl	(%rdi), %eax
	ret
	.size	_Z1fPi, .-_Z1fPi
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
