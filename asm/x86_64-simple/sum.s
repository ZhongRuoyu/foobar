.globl Sum
Sum:
.globl _Sum
_Sum:
  xorl %eax, %eax
.Lloop:
  cmpq $0, %rsi
  jle .Ldone
  addl (%rdi), %eax
  addq $4, %rdi
  decq %rsi
  jmp .Lloop
.Ldone:
  ret
