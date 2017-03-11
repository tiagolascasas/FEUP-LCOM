.global _copyBuffer
.global _cleanBuffer

.text

/*in C syntax: copyBuffer(char* bf1, char* bf2, int size)*/
_copyBuffer:
	pushl %ebp				/* function prologue*/
	movl %esp, %ebp
	pushl %edi				/* assures %edi is not modified*/
	pushl %esi				/* same for %esi */
	movl 8(%ebp), %edi		/* %edi = bf1 */
	movl 12(%ebp), %esi		/* %esi = bf2 */
	movl 16(%ebp), %ecx		/* %ecx = size */
	rep movsb				/* copy 0(%esi) to 0(%edi) %ecx times,
							incrementing %edi and %esi by 1 each time */
	popl %esi				/* restores original %esi */
	popl %edi				/* restores original %edi */
	leave					/* function epilogue */
	ret

/*in C syntax: cleanBuffer(char* bf1, int size, short color)*/
_cleanBuffer:
	pushl %ebp				/* function prologue*/
	movl %esp, %ebp
	pushl %edi				/* assures %edi is not modified*/
	movl 8(%ebp), %edi		/* %edi = bf1 */
	movl 12(%ebp), %ecx		/* %ecx = size */
	shr $2, %ecx			/* dealing with two bytes per "iteration",
							so reduce size by half*/
	movw 16(%ebp), %ax		/* %eax = color */
	rep stosw				/* copy %ax to 0(%edi) %ecx times,
							incrementing %edi by 2 each time */
	popl %edi				/* restores original edi */
	leave					/* function epilogue */
	ret
