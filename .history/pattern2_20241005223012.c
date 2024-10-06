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
        sleep(sleep_times[ix]);  // Sleep for the generated time
      } else {
        // Last child: no more children to create, just sleep
        printf("Child %d (PID: %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
        sleep(sleep_times[ix]);  // Last child sleeps
      }
      exit(0);  // Child exits after sleeping
    } else {
      pids_array[ix] = pid;  // Store the PID of the created child in the parent
    }
  }

  // Parent waits for all child processes to exit
  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(pids_array[ix], NULL, 0);  // Wait for each specific child to finish
    printf("Child %d (PID: %d) has exited\n", ix, pids_array[ix]);
  }

  printf("** Pattern 2: All children have exited **\n");
}
