#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void sleep_random() {
  int random_time = rand() % 8 + 1;
  printf("Sleeping for %d seconds\n", random_time);
  sleep(random_time);
}

void fork_pattern_one(int num_processes) {
  pid_t pid[num_processes];

  for (int ix = 0; ix < num_processes; ix++) {
    pid[ix] = fork();

    if (pid[ix] < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid[ix] > 0) {
      printf("Main process created Process %d with PID %d\n", ix + 1, pid[ix]);
    } else if (pid[ix] == 0) {
      exit(0);
    }
  }

  // Wait for all initial child processes to finish
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
  }

  // Now create child processes to sleep
  for (int ix = 0; ix < num_processes; ix++) {
    pid[ix] = fork();

    if (pid[ix] < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid[ix] == 0) {
      // Child process
      printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
      sleep_random();
      printf("Process %d (PID: %d) exiting\n", ix + 1, getpid());
      exit(0);
    }
  }

  // Wait for all child processes to finish sleeping
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
  }
}