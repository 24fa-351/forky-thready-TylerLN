#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void rand_time() {
  srand(time(NULL));
  int sleep_time = rand() % 8 + 1;
  sleep(sleep_time);
}

void create_process(int num_processes) {
  pid_t pid;
  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();
    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());

      exit(0);
    }
  }
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Child process %d has finished.\n", ix + 1);
  }
}