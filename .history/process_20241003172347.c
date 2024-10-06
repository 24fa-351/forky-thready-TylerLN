#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_process(int n, int num_things, int pattern) {
  printf("Process %d beginning (PID: %d)\n", n, getpid());
  int sleep_time = rand() % 8 + 1;  // Sleep time between 1 and 8 seconds
  sleep(sleep_time);

  // Only create a child process if we haven't reached the maximum number
  if (n < num_things) {
    if (pattern == 1) {  // Pattern 1: Fork all processes before waiting
      printf("Process %d creating Process %d (PID: %d)\n", n, n + 1, getpid());
      pid_t pid = fork();
      if (pid == 0) {                              // Child process
        fork_process(n + 1, num_things, pattern);  // Continue creating children
        exit(0);                                   // Exit child process
      }
    } else if (pattern == 2) {  // Pattern 2: Fork one at a time
      printf("Process %d creating Process %d (PID: %d)\n", n, n + 1, getpid());
      pid_t pid = fork();
      if (pid == 0) {                              // Child process
        fork_process(n + 1, num_things, pattern);  // Continue creating children
        exit(0);                                   // Exit child process
      } else {
        wait(NULL);  // Parent waits for child to finish
      }
    }
  }
}

void create_processes(int pattern, int num_things) {
  if (pattern < 1 || pattern > 2) {
    printf("Invalid pattern. Please choose 1 or 2.\n");
    return;
  }
  srand(time(NULL));                     // Seed random number generator
  fork_process(1, num_things, pattern);  // Start from process 1
  while (wait(NULL) > 0);  // Wait for all child processes to finish
}
