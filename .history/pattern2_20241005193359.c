#include "pattern2.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_two(int num_processes) {
  pid_t pid;
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      perror("Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);
    } else {
      wait(NULL);
      printf("Process %d (PID: %d) creating Process %d (PID: %d)\n", ix + 1,
             pid, ix + 2, getpid());
    }
  }

  for (int ix = num_processes; ix != 0; ix--) {
    wait(NULL);
    printf("Process %d (PID: %d) exiting\n", ix, getpid());
  }
  wait(NULL);
  printf("All Processes have exited\n");
}
