#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv)
 {
  if (argc != 3)
 {
    printf("Usage: %s seed arraysize\n", argv[0]);
    return 1;
  }

  char* arg[4];
  for(int i = 0; i < 3; i++) {
    arg[i] = malloc(sizeof(char)*40);
  }
  strcpy(arg[0], "sequential_min_max");
  for (int i = 1; i < 3; i++) {
      strcpy(arg[i], argv[i]);
  }
  arg[3] = NULL;

  int pid = fork();
  if(pid == 0)
  {
    execv("sequential_min_max", arg);
  }
  int* status;
  wait(status);
  for(int i = 0; i< 4; i++) free(arg[i]);
  return 0;
}
