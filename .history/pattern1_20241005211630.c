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
      // It will not sleep yet; it will sleep later after all have been created
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, getpid(), sleep_times[ix]);
      exit(0);  // Child process exits immediately after creation
    } else {
      // This is the parent process
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, pid);
    }
  }

  // Parent process waits for all child processes to finish before sleeping them
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);  // Wait for any child process to finish
  }

  // Now the parent will let each child process sleep
  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();  // Fork again to let children sleep after they are created
    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      printf("Child Process %d (PID: %d) will sleep for %d seconds\n", ix,
             getpid(), sleep_times[ix]);
      sleep(sleep_times[ix]);  // Sleep for the random time
      printf("Child Process %d (PID: %d) finished sleeping and is exiting\n",
             ix, getpid());
      exit(0);  // Child process exits after sleeping
    }
  }

  // Parent process waits for all child processes to finish again
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);  // Wait for any child process to finish
  }

  printf("All child processes have finished.\n");
}
