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
  for (int ix = 1; ix <= num_processes; ix++) {
    pids[ix] = fork();

    if (pids[ix] < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pids[ix] == 0) {
      // Child process prints its beginning message
      printf("Process %d (PID: %d) beginning.\n", ix, getpid());
      sleep(rand_time());

      if (ix < num_processes) {
        // Child process creates the next process
        printf("Process %d (PID: %d) creating Process %d.\n", ix, getpid(),
               ix + 1);
      }

      // Child process exits after its work
      exit(0);
    }
  }

  // Parent waits for all child processes to finish
  for (int ix = num_processes; ix >= 1; ix--) {
    waitpid(pids[ix], NULL, 0);
    printf("Process %d (PID: %d) exiting.\n", ix, pids[ix]);
  }

  printf("All processes have completed.\n");
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