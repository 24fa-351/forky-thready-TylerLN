#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t pid;
  srand(time(NULL));

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      perror("Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d (PID: %d) beginning\n", ix + 1, getpid());
      sleep(rand_time());
      exit(0);
    } else {
      pids[ix] = pid;
    }
  }

  for (int iy = 0; iy < num_processes; iy++) {
    waitpid(pids[iy], NULL, 0);
    printf("Process %d (PID: %d) exiting\n", iy + 1, pids[iy]);
  }

  printf("All Processes have exited\n");
}
