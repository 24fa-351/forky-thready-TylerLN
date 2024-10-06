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
  srand(time(NULL));

  printf("Parent: Creating %d child processes\n", num_processes);
  fflush(stdout);

  // Step 1: Create all child processes
  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {  // Child process code
      printf("Child %d (PID: %d): starting\n", ix, getpid());

      // Child process waits until all processes are created
      while (1) {
        // Check if the parent has created all child processes
        if (getppid() == 1) {  // Parent has terminated
          exit(0);             // Exit if parent is gone
        }
        sleep(1);  // Small sleep to prevent busy waiting
        if (ix == num_processes - 1) {
          break;  // Last child will break the loop to proceed
        }
      }

      // Now all children can sleep
      printf("Child %d (PID: %d), sleeping for %d seconds\n", ix, getpid(),
             sleep_times[ix]);
      sleep(sleep_times[ix]);  // Child sleeps for its assigned time
      printf("Child %d (PID: %d) finished sleeping and is exiting\n", ix,
             getpid());
      exit(0);  // Child process exits after sleeping
    } else {
      pids_array[ix] = pid;  // Store child PID in parent process
    }
  }

  printf("All Child Processes Created\n");

  // Step 2: Parent waits for all child processes to finish
  for (int ix = 0; ix < num_processes; ix++) {
    int status;
    pid_t finished_pid = wait(&status);  // Wait for any child process to finish

    // Find which child process finished
    for (int j = 0; j < num_processes; j++) {
      if (pids_array[j] == finished_pid) {
        printf("Child %d (PID: %d) has exited\n", j, finished_pid);
        break;
      }
    }
  }

  printf("** Pattern 2: All children have exited **\n");
}
