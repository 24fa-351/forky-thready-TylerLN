#include "pattern2.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_two(int num_processes) {
  pid_t pid;
  pid_t pids_array[num_processes];
  int sleep_times[num_processes];
  srand(time(NULL));  // Seed the random number generator

  printf("Parent: Creating %d child processes\n", num_processes);
  fflush(stdout);

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {  // Child process code
      printf("Child %d (PID: %d): starting\n", ix, getpid());

      if (ix < num_processes - 1) {
        printf(
            "Child %d (PID: %d), sleeping %d seconds after creating child %d\n",
            ix, getpid(), sleep_times[ix], ix + 1);
      } else {
        printf("Child %d (PID: %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
      }

      sleep(sleep_times[ix]);  // Each child sleeps for its own designated time
      printf("Child %d (PID: %d) has exited\n", ix, getpid());
      exit(0);
    } else {
      pids_array[ix] = pid;  // Parent stores the child's PID
    }
  }

  // Parent process waits for all children to exit
  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(pids_array[ix], NULL, 0);  // Wait for each child to complete
  }

  printf("** Pattern 2: All children have exited **\n");
}
