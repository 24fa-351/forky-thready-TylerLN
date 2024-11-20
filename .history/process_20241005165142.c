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
  pid_t pids[num_processes];  // Array to store the child PIDs
  srand(time(NULL));

  // Forking the child processes
  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {  // Child process
      printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);         // Child exits after sleep
    } else {           // Parent process
      pids[ix] = pid;  // Store the child's PID
    }
  }

  // Waiting for all child processes to finish
  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(pids[ix], NULL, 0);  // Wait for each specific child process
    printf("Process %d (PID: %d) exiting\n", ix + 1,
           pids[ix]);  // Print the child's PID
  }

  printf("All Processes have exited\n");
}

void fork_pattern_two(int num_processes) {
  pid_t pid;
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    if (ix == 0) {
      printf("Main creating Process %d\n", ix + 1);
    } else {
      printf("Process %d (PID %d) creating Process %d\n", ix, getpid(), ix + 1);
    }
    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      int sleep_time = rand_time();
      printf("Process %d (PID %d) slept for %d seconds\n", ix + 1, getpid(),
             sleep_time);
      sleep(sleep_time);

      if (ix + 1 < num_processes) {
        printf("Process %d (PID %d) creating Process %d\n", ix + 1, getpid(),
               ix + 2);
        pid = fork();

        if (pid < 0) {
          fprintf(stderr, "Fork failed.\n");
          exit(1);
        } else if (pid == 0) {
          continue;  // Child process continues the loop
        } else {
          wait(NULL);  // Parent process waits for the child to finish
        }
      }
      printf("Process %d (PID: %d) exiting\n", ix + 1, getpid());
      exit(0);
    } else {
      wait(NULL);  // Parent process waits for the child to finish
      break;       // Parent process exits the loop
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