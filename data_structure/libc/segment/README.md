
Let us examine segement.c file.

```C
	char*s = "hello";
	char sar[] = "hello";
	char content[32];

	int main(int argc, char*argv[]) {
		char*ps = "phello";
		content[0] = 1;
		sar[3] = 1;
		// sar++; // not allowed
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
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	$.LC1, -8(%rbp)
	movb	$1, content(%rip)
	movb	$1, sar+3(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
```

Again for private variable in main, the compiler does not bother to create a name.

The `.text` segement is generally saved in ROM in embedded system. While in desktop it is saved in RAM.
