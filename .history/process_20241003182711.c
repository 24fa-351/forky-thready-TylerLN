#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int rand_time() {
  srand(time(NULL));
  int sleep_time = rand() % 8 + 1;
  sleep(sleep_time);
  return sleep_time;
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
      sleep(rand_time);
      exit(0);
    }
  }
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Child process %d has finished after %d seconds.\n", ix + 1,
           rand_time());
  }
}