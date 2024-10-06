#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Function to fork and create processes
void fork_process(int n, int num_things) {
  // Base case: stop if the limit of processes is reached
  if (n > num_things) {
    return;
  }

  // Create a new process
  pid_t pid = fork();  // Fork a new process
  if (pid < 0) {
    perror("Fork failed");
    exit(1);
  }

  if (pid == 0) {  // Child process
    // Random sleep time between 1 and 8 seconds
    int sleep_time = rand() % 8 + 1;
    sleep(sleep_time);

    // Print the process beginning message
    printf("Process %d beginning (PID: %d)\n", n, getpid());

    // Create the next process if the limit hasn't been reached
    if (n < num_things) {
      fork_process(n + 1, num_things);  // Recursive call for child
    }
    exit(0);  // Child exits after creating the next process
  } else {    // Parent process
    // Print the process beginning message for the parent
    printf("Process %d beginning (PID: %d)\n", n, getpid());
  }
}

// Function to start the process creation
void create_processes(int num_things) {
  srand(time(NULL));            // Seed the random number generator
  fork_process(1, num_things);  // Start from process 1

  // Ensure the initial parent waits for all child processes to finish
  while (wait(NULL) > 0);  // Wait for all children to finish
}
