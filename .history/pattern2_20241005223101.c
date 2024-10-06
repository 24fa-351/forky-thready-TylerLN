#include "pattern2.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_two(int num_processes) {
  pid_t pid;
  pid_t pids_array[num_processes];  // Array to store child PIDs
  int sleep_times[num_processes];   // Array to store sleep times
  srand(time(NULL));                // Seed for random sleep times

  printf("Parent: Creating %d child processes\n", num_processes);
  fflush(stdout);

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();        // Create a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {  // Child process
      printf("Child %d (PID: %d): starting\n", ix, getpid());

      if (ix < num_processes - 1) {
        // If not the last child, print message and sleep after creating the
        // next child
        printf(
            "Child %d (PID: %d), sleeping %d seconds after creating child %d\n",
            ix, getpid(), sleep_times[ix], ix + 1);
      } else {
        // Last child: no more children to create, just sleep
        printf("Child %d (PID: %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
            }
      exit(0);  //
    } else {
      pids_array[ix] = pid;
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(pids_array[ix], NULL, 0);
    sleep(sleep_times[ix]);
    printf("Child %d (PID: %d) has exited\n", ix, pids_array[ix]);
  }

  printf("** Pattern 2: All children have exited **\n");
}
