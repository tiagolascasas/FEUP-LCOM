#include "i8042.h"

.global _kbd_read_asm

.text
_kbd_read_asm:					/*the function was based largely on kbd_read_c*/
	movl $RETRIES, %ecx			/*set ecx as the retries counter*/
retries_loop:
	inb $STAT_REG, %al			/*get status register info*/
	test $OBF, %al				/*check if output buffer is full*/
	jz failed					/*if it isn't, retry*/
	movb %al, %dl				/*copy status info to dl, because al will be needed for in*/
	inb $OUT_BUF, %al			/*read byte from OUT_BUF*/
	test $(PAR | TIMEOUT), %dl	/*check Parity Error and Timeout with status info*/
	jnz error 					/*if any of them is set, jump to error*/
	jmp end
failed:
	pushl %ecx
	pushl %eax
	pushl %edx
	pushl $DELAY_US
	call _micros_to_ticks
	add $4, %esp
	push %eax
	call _tickdelay
	add $4, %esp
	popl %edx
	popl %eax
	popl %ecx
	loop retries_loop			/*decrement ecx (n of retries) and retry*/
error:
	movb $0, %al
end:
	ret

