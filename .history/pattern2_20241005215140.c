#include "pattern2.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_two(int num_processes) {
  pid_t pid;
  pid_t pids[num_processes];
  int sleep_times[num_processes];
  srand(time(NULL));

  printf("** Pattern 2: Creating %d processes **\n", num_processes);
  fflush(stdout);

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] = rand() % 8 + 1;
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Child %d (pid %d): starting\n", ix, getpid());
      if (ix < num_processes - 1) {
        printf(
            "Child %d (pid %d), sleeping %d seconds after creating child %d\n",
            ix, getpid(), sleep_times[ix], ix + 1);
        sleep(sleep_times[ix]);
      } else {
        printf("Child %d (pid %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
        sleep(sleep_times[ix]);
      }
      exit(0);
    } else {
      pids[ix] = pid;
      printf("Parent: created child %d (pid %d)\n", ix, pid);
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Parent: child %d (pid %d) has exited\n", ix, pids[ix]);
  }

  printf("** Pattern 2: All children have exited **\n");
}