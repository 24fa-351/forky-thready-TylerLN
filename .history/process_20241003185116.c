#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int rand_time() {
  int sleep_time = rand() % 10 + 5;
  return sleep_time;
}

void fork_pattern_one(int num_processes) {
  pid_t pid;
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Process %d (PID: %d) exiting\n", ix + 1, getpid());
  }
}

void fork_pattern_two(int num_processes) {
  pid_t pid;
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    if (ix == 0) {
      printf("Main creating Process %d\n", ix + 1);
    } else {
      printf("Process %d creating Process %d\n", ix, ix + 1);
      pid = fork();

      if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
      } else if (pid == 0) {
        printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
        sleep(rand_time());
        exit(0);
      } else {
        wait(NULL);
        printf("Process %d (PID: %d) exiting\n", ix + 1, getpid());
      }
    }
  }

  void choose_pattern(int pattern, int num_processes) {
    if (pattern == 1) {
      fork_pattern_one(num_processes);
    } else if (pattern == 2) {
      fork_pattern_two(num_processes);
    } else {
      fprintf(stderr, "Invalid pattern number.\n");
      exit(1);
    }
  }