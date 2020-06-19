#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>

int result = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

struct MultiArgs {
  int mod;
  int begin;
  int end;
};

void multiply(const struct MultiArgs *args)
{
  int i;
  int prod = 1;
  for(i = (*args).begin; i < (*args).end; i++) {
    if (i % (*args).mod == 0)
        continue;
	prod *= (i % (*args).mod);
    prod %= (*args).mod;
  }
  pthread_mutex_lock(&mut);
  result *= prod;
  result %= (*args).mod;
  pthread_mutex_unlock(&mut);
}


int main(int argc, char **argv) {
  if (argc != 4) {
      printf("usage: %s k tnum m\n", argv[0]);
      return 1;
  }

  int threads_num = atoi(argv[2]);
  int k = atoi(argv[1]); // factoral argument
  int mod = atoi(argv[3]); // mod base
  int j;

  pthread_t threads[threads_num];

  int array_step = k / threads_num;
  int last_step = array_step + k % threads_num;

  struct MultiArgs args[threads_num];

  for (j = 0; j < threads_num; j++)
  {
    int local_step = j < threads_num - 1 ? array_step : last_step;
    args[j].begin = j * array_step + 1;
    args[j].end = j * array_step + local_step + 1;
    args[j].mod = mod;
    if (pthread_create(&threads[j], NULL, (void*)multiply, (void*)&args[j]))
    {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  for (j = 0; j < threads_num; j++) {
    pthread_join(threads[j], NULL);
  }

  printf("result: %d\n", result);

  return -1;
}
