#include "thread.h"
#include "thread-sync.h"

#define N 5
mutex_t lk;
cond_t cv;
int avail[N];

void Tphilosopher(int id) {
  int lhs = (N + id - 1) % N;
  int rhs = id % N;
  while (1) {
    mutex_lock(&lk);
    while (!(avail[lhs] && avail[rhs])) {
      cond_wait(&cv, &lk);
    }
    avail[lhs] = avail[rhs] = 0;
    mutex_unlock(&lk);

    printf("T%d Got %d\n", id, lhs + 1);
    printf("T%d Got %d\n", id, rhs + 1);
    
    // Eat

    mutex_lock(&lk);
    avail[lhs] = avail[rhs] = 1;
    cond_broadcast(&cv);
    mutex_unlock(&lk);
  }
}



int main(int argc, char *argv[]) {
  for (int i = 0; i < N; ++i) {
    avail[i] = 1;
  }
  for (int i = 0; i < N; i++) {
    create(Tphilosopher);
  }
}
