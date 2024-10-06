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

  // Array to hold random sleep times for each child
  int sleep_times[num_processes];

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();        // Fork a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, pid);

      exit(0);  // Child process exits after sleeping
    } else {
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, getpid(), sleep_times[ix]);
    }
  }

  wait(NULL);  // Wait for the last child to finish
  for (int ix = 0; ix < num_processes;
       ix++) {               // Wait for any child process to finish
    sleep(sleep_times[ix]);  // Sleep for the random time
    printf("Child Process %d (PID: %d) finished sleeping and is exiting\n", ix,
           getpid());
  }

  printf("All child processes have finished.\n");
}
