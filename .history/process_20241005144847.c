#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int rand_time() {
  int sleep_time = rand() % 8 + 1;
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
  printf("All Processes have exited\n");
}

void fork_pattern_two(int num_processes) {
  pid_t pids[num_processes];
  srand(time(NULL));

  // Create all processes first
  for (int ix = 0; ix < num_processes; ix++) {
    pids[ix] = fork();

    if (pids[ix] < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pids[ix] == 0) {
      // Child process
      printf("Process %d (PID: %d) creating Process %d\n", ix + 1, getpid(),
             ix + 2);
      sleep(rand_time());
      exit(0);  // Each child process exits after sleeping
    } else {
      // Parent process
      if (ix < num_processes - 1) {
        printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      }
    }
  }

  // After creating all processes, wait for them to exit
  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(pids[ix], NULL, 0);
    printf("Process %d (PID: %d) exiting\n", ix + 1, pids[ix]);
  }

  printf("All processes have exited\n");
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