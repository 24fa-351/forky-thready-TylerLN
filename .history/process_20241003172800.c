#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_process(int n, int num_things, int pattern) {
  if (n > num_things) {
    return;  // Base case: stop creating processes if the limit is reached
  }

  printf("Process %d beginning (PID: %d)\n", n, getpid());
  int sleep_time = rand() % 8 + 1;  // Sleep time between 1 and 8 seconds
  sleep(sleep_time);

  // Only create a child process if we haven't reached the maximum number
  pid_t pid = fork();
  if (pid < 0) {
    perror("Fork failed");
    exit(1);
  }

  if (pid == 0) {  // Child process
    // Child continues by creating the next process
    printf("Process %d creating Process %d (PID: %d)\n", n, n + 1, getpid());
    fork_process(n + 1, num_things,
                 pattern);  // Recursive call for child process
    exit(0);                // Exit child process after finishing
  } else {                  // Parent process
    // Handle waiting based on pattern
    if (pattern == 2) {
      wait(NULL);  // Wait for the child to finish
    } else {
      // For pattern 1, parent does not wait here
    }
  }
}

void create_processes(int pattern, int num_things) {
  srand(time(NULL));                     // Seed random number generator
  fork_process(1, num_things, pattern);  // Start from process 1
  while (wait(NULL) > 0);  // Wait for all child processes to finish
}
