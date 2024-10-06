#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t pid;
  pid_t pids_array[num_processes];
  int sleep_times[num_processes];
  srand(time(NULL));

  printf("Parent: Creating %d child processes\n", num_processes);
  fflush(stdout);

  for (int child_index = 0; child_index < num_processes; child_index++) {
    sleep_times[child_index] = rand() % 8 + 1;
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Parent: Created Child Process %d (PID: %d)\n", child_index,
             getpid());
      exit(0);
    } else {
      pids_array[child_index] = pid;
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
           ix, pids_array[ix], sleep_times[ix]);
    sleep(sleep_times[ix]);
  }

  printf("All Child Processes Created\n");

  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Child Process %d (PID: %d) finished sleeping and is exiting\n", ix,
           pids_array[ix]);
  }

  printf("All child processes exited\n");
}
