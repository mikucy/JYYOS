#include <stdio.h>

typedef struct {
  int pc, n;
  char from, via, to;
} Frame;

#define call(...) ({ *(++top) = (Frame) {.pc = 0, __VA_ARGS__}; })
#define go(n) ({ f->pc = n - 1; }) // 注意：这里为什么是n - 1？因为for循环内会自动让f->pc++
#define ret() ({ --top; }) // 注意：这里需要设置f->pc = 0吗？不需要，因为当前的栈帧都没用了，下次循环时f会指向上一个栈帧，并从该栈帧的pc继续执行

void hanoi_nr(int n, char from, char via, char to) {
  Frame stack[64], *top = stack - 1;
  call(n, from, via, to);
  for (Frame *f; (f = top) >= stack; f->pc++) {
    switch (f->pc) {
    case 0:
      if (f->n == 1) {
        printf("%c -> %c\n", f->from, f->to);
        go(4);
      }
      break;
    case 1:
      call(f->n - 1, f->from, f->to, f->via);
      break;
    case 2:
      call(1, f->from, f->via, f->to);
      break;
    case 3:
      call(f->n - 1, f->via, f->from, f->to);
      break;
    case 4:
      ret();
      break;
    }
  }
}

int main() { hanoi_nr(3, 'A', 'B', 'C'); }