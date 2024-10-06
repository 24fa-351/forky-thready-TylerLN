#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Function to fork and create processes recursively for Pattern 2
void fork_process(int n, int num_things) {
  // Base case: stop if the limit of processes is reached
  if (n > num_things) {
    return;
  }

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
    exit(0);                          // Child exits after completing its task
  } else {                            // Parent process
    wait(NULL);                       // Wait for the child to finish
    fork_process(n + 1, num_things);  // Recursive call for the next process
  }
}

// Function to start the process creation based on the specified pattern
void create_processes(int pattern, int num_things) {
  srand(time(NULL));  // Seed the random number generator

  if (pattern == 1) {
    for (int n = 1; n <= num_things; n++) {
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
        exit(0);  // Child exits after completing its task
      }

      // Add a small delay to ensure correct order of process creation
      usleep(100000);  // 100 milliseconds
    }

    // Ensure the initial parent waits for all child processes to finish
    while (wait(NULL) > 0);
  } else if (pattern == 2) {
    fork_process(1, num_things);  // Start from process 1 for sequential forking
  }
}

int main() {
  int pattern = 1;     // Example pattern
  int num_things = 5;  // Example number of processes

  create_processes(pattern, num_things);

  return 0;
}