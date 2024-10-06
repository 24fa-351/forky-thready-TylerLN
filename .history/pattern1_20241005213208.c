#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t pid;
  srand(time(NULL));
  int sleep_times[num_processes];

  // Create child processes
  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();        // Fork a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      for (int ix = 0; ix < num_processes; ix++) {
        wait(NULL);  // Wait for any child process to finish
      }
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, getpid(), sleep_times[ix]);
      sleep(sleep_times[ix]);  // Sleep for the random time
      printf("Child Process %d (PID: %d) finished sleeping and is exiting\n",
             ix, getpid());
      exit(0);  // Child process exits after sleeping
    } else {
      // This is the parent process
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, pid);
        }
  }

  // Parent process waits for all child processes to finish

  printf("All child processes have exited.\n");
}
