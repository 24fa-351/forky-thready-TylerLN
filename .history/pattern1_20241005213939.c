#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t pid;
  pid_t pids[num_processes];
  int sleep_times[num_processes];
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] = rand() % 8 + 1;
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, getpid());
      exit(0);
    } else {
      pids[ix] = pid;
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             ix, pid, sleep_times[ix]);
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
  }

  printf("All Child Processes Created\n");

  for (int ix = 0; ix < num_processes; ix++) {
    sleep(sleep_times[ix]);
    printf("Child Process %d (PID: %d) finished sleeping and is exiting\n", ix,
           pids[ix]);
  }

  printf("All child processes exited\n");
}
