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
  pid_t pids[num_processes];  // Array to store the child PIDs
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    if (ix == 0) {
      printf("Main creating Process %d\n", ix + 1);
    }

    pid_t pid = fork();  // Fork the process

    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {  // Child process
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      int sleep_time = rand_time();
      sleep(rand_time());

      if (ix + 1 < num_processes) {
        printf("Process %d (PID %d) creating Process %d\n", ix + 1, getpid(),
               ix + 2);
        pid_t child_pid = fork();

        if (child_pid < 0) {
          fprintf(stderr, "Fork failed.\n");
          exit(1);
        } else if (child_pid == 0) {
          continue;  // Child process continues the loop
        } else {
          pids[ix + 1] = child_pid;  // Store the child PID
          waitpid(child_pid, NULL,
                  0);  // Parent process waits for the child to finish
        }
      }

      printf("Process %d (PID: %d) exiting\n", ix + 1, getpid());
      exit(0);
    } else {                  // Parent process
      pids[ix] = pid;         // Store the child PID
      waitpid(pid, NULL, 0);  // Wait for the child process to finish
      break;                  // Parent process exits the loop
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    printf("Process %d (PID: %d) exited\n", ix + 1, pids[ix]);
  }

  printf("All Processes have exited\n");
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