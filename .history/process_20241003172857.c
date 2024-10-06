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

  if (n < num_things) {  // Only create a child if we haven't reached the max
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
      exit(0);                // Child exits after completing
    } else {                  // Parent process
      // For pattern 2, wait for the child to finish
      if (pattern == 2) {
        wait(NULL);  // Parent waits for the child
      }
      // For pattern 1, do not wait, just return
    }
  }

  // After this point, both parent and child should properly exit
  if (n == 1) {              // This is only for the very first process
    while (wait(NULL) > 0);  // Ensure parent waits for all children
  }
}

void create_processes(int pattern, int num_things) {
  srand(time(NULL));                     // Seed random number generator
  fork_process(1, num_things, pattern);  // Start from process 1
}
