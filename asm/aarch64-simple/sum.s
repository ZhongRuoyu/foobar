.globl Sum
Sum:
.globl _Sum
_Sum:
  mov x9, x0
  mov w0, wzr
.Lloop:
  cmp x1, #0
  ble .Ldone
  ldr w10, [x9], #4
  add w0, w0, w10
  sub x1, x1, #1
  b .Lloop
.Ldone:
  ret
