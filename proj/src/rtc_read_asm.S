#include "RTC_defs.h"

.global _rtc_read_asm

.text

/* in C syntax: rtc_read_asm(int addr) */
_rtc_read_asm:
	pushl %ebp					/* function prologue*/
	movl %esp, %ebp
	xorl %eax, %eax
	movb 8(%ebp), %al			/* %edx = addr */
	outb %al, $RTC_ADDR_REG
	xorl %eax, %eax
	inb $RTC_DATA_REG, %al
	leave
	ret

