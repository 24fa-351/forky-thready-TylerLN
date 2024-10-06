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

  printf("Parent process (PID: %d) will create %d child processes.\n", getpid(),
         num_processes);

  int sleep_times[num_processes];  // Array to store sleep times for each child

  // Create child processes
  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Assign random sleep time for each child
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // Child process
      sleep(sleep_times[ix]);  // Simulate work
      printf("Child Process %d (PID: %d) finished sleeping and is exiting\n",
             ix, getpid());
      exit(0);  // Exit successfully
    }
    // Parent process will print the message below after creating all children
  }

  // Parent prints the details of created children
  for (int ix = 0; ix < num_processes; ix++) {
    printf("Parent: Created Child Process %d (will sleep for %d seconds)\n", ix,
           sleep_times[ix]);
  }

  // Wait for all child processes to exit
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);  // Wait for any child process to exit
  }

  printf("All child processes have finished.\n");
}
