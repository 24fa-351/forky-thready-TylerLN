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

  for (int ix = 0; ix < num_processes; ix++) {
    int rand_time = rand() % 8 + 1;
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, getpid(), rand_time);
      sleep(rand_time);
      printf("Child Process %d (PID: %d) finished sleeping and is exiting\n",
             ix, getpid());
      exit(0);
    } else if (pid > 0) {
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, pid);
    }
  }
  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(NULL) printf("Process %d (PID: %d) exiting\n", ix + 1, pids[ix]);
  }

  printf("All child processes have finished.\n");
}
