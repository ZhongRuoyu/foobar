.globl Strlen
Strlen:
.globl _Strlen
_Strlen:
  xorq %rax, %rax
.Lloop:
  cmpb $0, (%rdi)
  je .Ldone
  incq %rax
  incq %rdi
  jmp .Lloop
.Ldone:
  ret
