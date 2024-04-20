.global Strlen
Strlen:
.global _Strlen
_Strlen:
  mov x9, x0
  mov x0, xzr
.Lloop:
  ldrb w10, [x9]
  cbz w10, .Ldone
  add x0, x0, #1
  add x9, x9, #1
  b .Lloop
.Ldone:
  ret
