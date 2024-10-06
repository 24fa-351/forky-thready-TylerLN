#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#include "process.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("invalid args");
    return 1;
  }

  int num_processes = atoi(argv[1]);

  if (num_processes < 1 || num_processes > 256) {
    printf("Error: Value not in range\n");
    return 1;
  }

  srand(time(NULL));

  fork_pattern_one(num_processes);

  return 0;
}
