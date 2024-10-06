#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Function to fork and create processes recursively
void fork_process(int n, int num_things, int pattern) {
  // Base case: stop if the limit of processes is reached
  if (n > num_things) {
    return;
  }

  printf("Process %d beginning (PID: %d)\n", n, getpid());

  // Random sleep time between 1 and 8 seconds
  int sleep_time = rand() % 8 + 1;
  sleep(sleep_time);

  // Only create a new process if we haven't reached the maximum
  if (n < num_things) {
    pid_t pid = fork();  // Fork a new process
    if (pid < 0) {
      perror("Fork failed");
      exit(1);
    }

    if (pid == 0) {  // Child process
      // Child will create the next process
      printf("Process %d creating Process %d (PID: %d)\n", n, n + 1, getpid());
      fork_process(n + 1, num_things, pattern);  // Recursive call for child
      exit(0);  // Child exits after creating the next process
    } else {    // Parent process
      // Wait for the child process based on the pattern
      if (pattern == 2) {
        wait(NULL);  // Parent waits for the child to finish
      }
      // For pattern 1, do not wait here; all processes run concurrently
    }
  }
}

// Function to start the process creation based on the specified pattern
void create_processes(int pattern, int num_things) {
  srand(time(NULL));                     // Seed the random number generator
  fork_process(1, num_things, pattern);  // Start from process 1

  // Ensure the initial parent waits for all child processes to finish
  while (wait(NULL) > 0);
}
