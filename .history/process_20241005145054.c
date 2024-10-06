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
  pid_t pid;
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      // Fork failed
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      // Child process prints its beginning message
      printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());

      if (ix < num_processes - 1) {
        // Child process creates the next process
        printf("Process %d (PID: %d) creating Process %d\n", ix + 1, getpid(),
               ix + 2);
      }

      // Child process exits (so that we do not enter an infinite fork loop)
      exit(0);
    } else {
      // Parent process should not wait here; it proceeds to the next loop
      // iteration to create more processes We only wait for all processes after
      // they've all been created
    }
  }

  // Parent waits for all child processes to finish
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);  // Wait for each child process to finish
    printf("Process %d exiting\n", ix + 1);
  }

  printf("All processes have exited.\n");
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