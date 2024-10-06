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

  for (int child_index = 0; child_index < num_processes; child_index++) {
    sleep_times[child_index] = rand() % 8 + 1;
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Child %d (PID: %d): starting\n", child_index, getpid());

      if (child_index < num_processes - 1) {
        printf(
            "Child %d (PID: %d), sleeping %d seconds after creating child %d\n",
            child_index, getpid(), sleep_times[child_index], child_index + 1);
      } else {
        printf("Child %d (PID: %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
        sleep(sleep_times[ix]);
      }
      exit(0);
    } else {
      pids_array[ix] = pid;
      sleep(sleep_times[ix]);
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Child Process %d (PID: %d) finished sleeping and is exiting\n", ix,
           pids_array[ix]);
  }

  printf("** Pattern 2: All children have exited **\n");
}
