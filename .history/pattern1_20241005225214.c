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
    } else if (pid == 0) {  // Child process code
      printf("Child Process %d (PID: %d) created, will sleep for %d seconds\n",
             child_index, getpid(), sleep_times[child_index]);
      sleep(sleep_times[child_index]);  // Child sleeps for its assigned time
      printf("Child Process %d (PID: %d) finished sleeping and is exiting\n",
             child_index, getpid());
      exit(0);  // Child process exits after sleeping
    } else {
      pids_array[child_index] = pid;  // Store child PID in parent process
    }
  }

  // Parent waits for all child processes to finish
  for (int ix = num_processes; ix != 0; ix--) {
    waitpid(pids_array[ix], NULL, 0);
  }

  printf("All child processes exited\n");
}
