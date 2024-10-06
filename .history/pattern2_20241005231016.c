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

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] = rand() % 8 + 1;
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Child %d (PID: %d): starting\n", ix, getpid());

      if (ix < num_processes - 1) {
        printf(
            "Child %d (PID: %d), sleeping %d seconds after creating child %d\n",
            ix, getpid(), sleep_times[ix], ix + 1);
      } else {
        printf("Child %d (PID: %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
      }
      exit(0);
    } else {
      sleep(sleep_times[ix]);
      pids_array[ix] = pid;
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    int status;
    pid_t finished_pid = wait(&status);  // Wait for any child process to finish
    // Optionally, check for exit status if needed
    // if (WIFEXITED(status)) {
    //     printf("Child with PID %d exited with status %d\n", finished_pid,
    //     WEXITSTATUS(status));
    // }

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
