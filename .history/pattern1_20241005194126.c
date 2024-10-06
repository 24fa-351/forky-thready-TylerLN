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
  printf("** Pattern 1: Creating %d processes\n", num_processes);

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      perror("Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      int sleep_time = rand() % 8 + 1;
      printf("Process %d (pid %d) created: will sleep for %d seconds\n", ix,
             getpid(), sleep_time);
      sleep(sleep_time);
      exit(0);
    } else {
      printf("Parent: created child %d (pid %d)\n", ix, pid);
    }
  }

  printf("** Pattern 1: All processes created\n");

  for (int iy = 0; iy < num_processes; iy++) {
    int status;
    pid_t exited_pid = wait(&status);
    printf("Process %d (pid %d): exiting\n", iy, exited_pid);
  }

  printf("** Pattern 1: All children have exited\n");
}
