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

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();  // Fork a new process
    int rand_time = rand() % 8 + 1;

    if (pid < 0) {
      // If fork failed
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, getpid(), rand_time);
      sleep(rand_time);  // Sleep for the random time
      printf("Child Process %d (PID: %d) finished sleeping and is exiting\n",
             ix, getpid());
      exit(0);  // Child process exits after finishing its task
    } else {
      if (ix == 0) {
      }
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, pid);
    }
  }
}

// Parent process waits for all child processes to finish

printf("All child processes have been created.\n");
}
