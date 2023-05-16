#include "thread.h"
#include "thread-sync.h"

int n, count = 0;
mutex_t lk = MUTEX_INIT();
cond_t empty = COND_INIT(), full = COND_INIT();

void Tproduce() {
  while (1) {
    mutex_lock(&lk);
    while (count == n) {
      cond_wait(&empty, &lk);
    }
    printf("("); count++;
    cond_signal(&full);
    mutex_unlock(&lk);
  }
}

void Tconsume() {
  while (1) {
    mutex_lock(&lk);
    while (count == 0) {
      pthread_cond_wait(&full, &lk);
    }
    printf(")"); count--;
    cond_signal(&empty);
    mutex_unlock(&lk);
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  n = atoi(argv[1]);
  setbuf(stdout, NULL);
  for (int i = 0; i < 8; i++) {
    create(Tproduce);
    create(Tconsume);
  }
}
