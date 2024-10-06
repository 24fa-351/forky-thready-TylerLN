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

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();        // Fork a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, getpid());

      exit(0);
    } else {
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, getpid(), sleep_times[ix]);
    }
  }

  wait(NULL);
  printf("ALl Child Processes Created\n");  // Wait for the last child to finish
  for (int ix = 0; ix < num_processes; ix++) {
    sleep(sleep_times[ix]);
    printf("Child Process %d (PID: %d) finished sleeping and is exiting\n", ix,
           getpid());
  }

  printf("All child processes exited\n");
}
