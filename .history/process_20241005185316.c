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
  pid_t pids[num_processes];
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);
    } else {
      pids[ix] = pid;
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(pids[ix], NULL, 0);
    printf("Process %d (PID: %d) exiting\n", ix + 1, pids[ix]);
  }

  printf("All Processes have exited\n");
}

void fork_pattern_two(int num_processes) {
  pid_t pids[num_processes];
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    pid_t pid = fork();

    if (pid < 0) {
      perror("Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      pids[ix] = getpid();
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);
    } else {
      wait(NULL);
      if (ix + 1 < num_processes) {
        printf("Process %d (PID: %d) creating Process %d (PID: %d)\n", ix + 1,
               pids[ix], ix + 2, pid);
      }
    }

    for (int ix = num_processes; ix != 0; ix--) {
      wait(NULL);
      printf("Process %d (PID: %d) exiting\n", ix, getpid());
    }

    printf("All Processes have exited\n");
  }
}

void choose_pattern(int pattern, int num_processes) {
  if (pattern == 1) {
    fork_pattern_one(num_processes);
  } else if (pattern == 2) {
    fork_pattern_two(num_processes);
  } else {
    perror("Invalid pattern number.\n");
    exit(1);
  }
}