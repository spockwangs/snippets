    .data

    .text

.globl tigermain
tigermain:
    pushl %ebp
    movl %esp, %ebp
    addl $-16, %esp
L1:
    movl %esi, -16(%ebp)
    movl %edi, -12(%ebp)
    movl %ebx, -8(%ebp)
    movl $-4, %ebx
    addl %ebp, %ebx
    movl %ebx, %ebx
    movl $initArray, %edx
    movl $2, %ecx
    movl $0, %eax
    pushl %eax
    pushl %ecx
    call *%edx
    movl %eax, %eax
    movl %eax, (%ebx)
    movl $-4, %eax
    addl %ebp, %eax
    movl (%eax), %ecx
    movl $1, %eax
    movl $4, %ebx
    movl %eax, %eax
    mull %ebx
    addl %ecx, %eax
    movl (%eax), %edx
    movl $-4, %eax
    addl %ebp, %eax
    movl (%eax), %ecx
    movl $0, %eax
    movl $4, %ebx
    movl %eax, %eax
    mull %ebx
    addl %ecx, %eax
    movl %edx, (%eax)
    movl -8(%ebp), %ebx
    movl -12(%ebp), %edi
    movl -16(%ebp), %esi
    movl $L0, %ecx
    jmp *%ecx
L0:
    leave
    ret
