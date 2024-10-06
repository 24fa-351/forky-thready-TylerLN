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
    } else if (pid == 0) {
      printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);
    } else {
      pids[ix] = pid;
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

  // Create first process
  printf("Main creating Process 1\n");
  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed.\n");
    exit(1);
  } else if (pid == 0) {  // Child process 1
    printf("Process 1 (PID: %d) beginning\n", getpid());
    sleep(rand_time());

    // Create the subsequent processes
    for (int ix = 1; ix < num_processes; ix++) {
      pid = fork();  // Create next child process

      if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
      } else if (pid == 0) {  // Child process
        printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
        sleep(rand_time());
        exit(0);  // Exit after sleeping
      } else {
        printf("Process %d (PID: %d) creating Process %d (PID: %d)\n", ix,
               getpid(), ix + 1, pid);
        waitpid(pid, NULL, 0);  // Wait for the created child to finish
      }
    }
    // Final exit message for the last child process
    printf("Process %d (PID: %d) exiting\n", num_processes, getpid());
    exit(0);  // Exit after finishing all creations
  } else {
    // Parent process waits for the first child process to finish
    waitpid(pid, NULL, 0);
    printf("Main process exiting\n");
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