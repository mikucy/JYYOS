#include <sys/syscall.h>

.global _start
_start:
  movq $SYS_write, %rax  # write(
  movq $1,         %rdi  #  fd = 1,
  movq $st,        %rsi  #  buf = st,
  movq $(ed - st), %rdx  #  length = ed - st
  syscall                # );

  movq $SYS_exit,  %rax  # exit(
  movq $1,         %rdi  #  1
  syscall                # );

st:
  .ascii "\033[31;44mHello, World\n"
ed: