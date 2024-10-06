#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t pid;
  pid_t pids[num_processes];       // Store child process IDs
  int sleep_times[num_processes];  // Store sleep times for each child
  srand(time(NULL));               // Seed random number generator

  printf("Parent: Creating %d child processes\n", num_processes);
  fflush(stdout);

  // First loop: Create child processes
  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();        // Create a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, getpid());
      exit(0);
    } else {
      pids[ix] = pid;
    }
  }

  // Wait for all children to be created
  for (int ix = 0; ix < num_processes; ix++) {
    // waitpid(pids[ix], NULL, 0);  // Wait for each specific child to exit
    printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
           ix, pids[ix], sleep_times[ix]);
  }

  printf("All Child Processes Created\n");

  for (int ix = 0; ix < num_processes; ix++) {
    sleep(sleep_times[ix]);
    printf("Child Process %d (PID: %d) finished sleeping and is exiting\n", ix,
           pids[ix]);
  }

  printf("All child processes exited\n");
}
