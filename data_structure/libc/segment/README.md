
Let us examine segement.c file.

```C

char*s = "hello";
char sar[] = "hello";
char content[32];

int main(int argc, char*argv[]) {
	char psar[] = "parhello";
	char*ps = "phello";
	content[0] = 1;
	sar[3] = 1; // OK
	// sar++; // not allowed
	// s[2] = 1; // segmentation fault
	s = sar;
	s[2] = 1; // OK
	psar[3] = 1; // OK
	// ps[2] = 1; // segmentation fault
	ps = psar;
	ps[2] = 1; // OK
	return 0;
}
```

Here is the assembly generated for segment.c file. Note that both `s` and `sar` is in `global` aka `.data` segement. It seems `sar` is const pointer or not pointer at all(practically it is an array). And eventually it has an implecation that `sizeof(sar) = 6` is different to `sizeof(s) = 8`. There are "hello" and "phello" in readonly(`.rodata`) section. 

```asm
	.file	"segment.c"
	.globl	s
	.section	.rodata
.LC0:
	.string	"hello"
	.data
	.align 8
	.type	s, @object
	.size	s, 8
s:
	.quad	.LC0
	.globl	sar
	.type	sar, @object
	.size	sar, 6
sar:
	.string	"hello"
	.comm	content,32,32
	.section	.rodata
.LC1:
	.string	"phello"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1752326512, -32(%rbp)
	movl	$1869376613, -28(%rbp)
	movb	$0, -24(%rbp)
	movq	$.LC1, -40(%rbp)
	movb	$1, content(%rip)
	movb	$1, sar+3(%rip)
	movq	$sar, s(%rip)
	movq	s(%rip), %rax
	addq	$2, %rax
	movb	$1, (%rax)
	movb	$1, -29(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	addq	$2, %rax
	movb	$1, (%rax)
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L2
	call	__stack_chk_fail
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
```

Again for private variable in main, the compiler does not bother to create a name. It can reside in register or in stack memroy. Note that local variable value "parhello" is optimized into 1752326512 and 1869376613 numbers. I discovered it by changin the value of "parhello" to "parhellp". The diff of the assembly output is as follows,

```
39c39
< 	movl	$1886153829, -28(%rbp)
---
> 	movl	$1869376613, -28(%rbp)
```

