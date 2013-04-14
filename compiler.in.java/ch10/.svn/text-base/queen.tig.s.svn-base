    .data

L20:  .string "\n"

L13:  .string "\n"

L3:  .string " ."

L2:  .string " O"

    .text

.globl tigermain
tigermain:
    pushl %ebp
    movl %esp, %ebp
    addl $-40, %esp
L22:
    movl %esi, -40(%ebp)
    movl %edi, -36(%ebp)
    movl %ebx, -32(%ebp)
    movl $8, %eax
    movl %eax, -4(%ebp)
    movl $-8, %ebx
    addl %ebp, %ebx
    movl %ebx, %ebx
    movl $initArray, %edx
    movl $-4, %eax
    addl %ebp, %eax
    movl (%eax), %ecx
    movl $0, %eax
    pushl %eax
    pushl %ecx
    call *%edx
    movl %eax, %eax
    movl %eax, (%ebx)
    movl $-12, %ebx
    addl %ebp, %ebx
    movl %ebx, %ebx
    movl $initArray, %edx
    movl $-4, %eax
    addl %ebp, %eax
    movl (%eax), %ecx
    movl $0, %eax
    pushl %eax
    pushl %ecx
    call *%edx
    movl %eax, %eax
    movl %eax, (%ebx)
    movl $-16, %ebx
    addl %ebp, %ebx
    movl %ebx, %ebx
    movl $initArray, %eax
    movl $-4, %ecx
    addl %ebp, %ecx
    movl (%ecx), %edi
    movl $-4, %ecx
    addl %ebp, %ecx
    movl (%ecx), %edx
    addl %edi, %edx
    movl $1, %ecx
    subl %ecx, %edx
    movl $0, %ecx
    pushl %ecx
    pushl %edx
    call *%eax
    movl %eax, %eax
    movl %eax, (%ebx)
    movl $-20, %ebx
    addl %ebp, %ebx
    movl %ebx, %ebx
    movl $initArray, %eax
    movl $-4, %ecx
    addl %ebp, %ecx
    movl (%ecx), %edi
    movl $-4, %ecx
    addl %ebp, %ecx
    movl (%ecx), %edx
    addl %edi, %edx
    movl $1, %ecx
    subl %ecx, %edx
    movl $0, %ecx
    pushl %ecx
    pushl %edx
    call *%eax
    movl %eax, %eax
    movl %eax, (%ebx)
    movl $0, %eax
    movl %eax, -24(%ebp)
L14:
    movl $1, %eax
    movl %eax, %eax
    movl $-24, %ebx
    addl %ebp, %ebx
    movl (%ebx), %ecx
    movl $-4, %ebx
    addl %ebp, %ebx
    movl (%ebx), %ebx
    cmpl %ebx, %ecx
    jl L15
L16:
    movl $0, %eax
    movl %eax, %eax
L15:
    movl $0, %ebx
    cmpl %ebx, %eax
    je L17
L18:
L19:
    movl $0, %eax
    movl %eax, -28(%ebp)
L7:
    movl $1, %eax
    movl %eax, %eax
    movl $-28, %ebx
    addl %ebp, %ebx
    movl (%ebx), %ecx
    movl $-4, %ebx
    addl %ebp, %ebx
    movl (%ebx), %ebx
    cmpl %ebx, %ecx
    jl L8
L9:
    movl $0, %eax
    movl %eax, %eax
L8:
    movl $0, %ebx
    cmpl %ebx, %eax
    je L10
L11:
L12:
    movl %ebp, %ebp
    movl $-12, %eax
    addl %ebp, %eax
    movl (%eax), %ecx
    movl $-24, %eax
    addl %ebp, %eax
    movl (%eax), %eax
    movl $4, %ebx
    movl %eax, %eax
    mull %ebx
    addl %ecx, %eax
    movl (%eax), %ebx
    movl $-28, %eax
    addl %ebp, %eax
    movl (%eax), %eax
    cmpl %eax, %ebx
    je L4
L5:
    movl $L3, %eax
    movl %eax, %eax
L6:
    movl $print, %ebx
    pushl %eax
    pushl %ebp
    call *%ebx
    movl $-28, %eax
    addl %ebp, %eax
    movl (%eax), %ebx
    movl $1, %eax
    addl %ebx, %eax
    movl %eax, -28(%ebp)
    movl $L7, %eax
    jmp *%eax
L17:
L0:
    movl $print, %ebx
    movl $L20, %eax
    pushl %eax
    pushl %ebp
    call *%ebx
    movl -32(%ebp), %ebx
    movl -36(%ebp), %edi
    movl -40(%ebp), %esi
    movl $L21, %ecx
    jmp *%ecx
L23:
    movl $L19, %eax
    jmp *%eax
L10:
L1:
    movl $print, %ebx
    movl $L13, %eax
    pushl %eax
    pushl %ebp
    call *%ebx
    movl $-24, %eax
    addl %ebp, %eax
    movl (%eax), %ebx
    movl $1, %eax
    addl %ebx, %eax
    movl %eax, -24(%ebp)
    movl $L14, %eax
    jmp *%eax
L24:
    movl $L12, %eax
    jmp *%eax
L4:
    movl $L2, %eax
    movl %eax, %eax
    movl $L6, %ebx
    jmp *%ebx
L21:
    leave
    ret
