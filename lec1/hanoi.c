#include <stdio.h>

void hanoi(int n, char from, char via, char to) {
  if (n == 1) {
    printf("%c -> %c\n", from, to);
    return;
  }
  hanoi(n - 1, from, to, via);
  hanoi(1, from, via, to);
  hanoi(n - 1, via, from, to);
}

int main() {
  hanoi(3, 'A', 'B', 'C');
}
