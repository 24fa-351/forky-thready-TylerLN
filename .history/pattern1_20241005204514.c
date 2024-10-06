#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t pid;
  pid_t childwait;
  srand(time(NULL));
  pid = fork();

  for (int ix = 0; ix < num_processes; ix++) {
    int rand_time = rand() % 8 + 1;
    if (pid == 0) {
      printf("Child Process %d (PID: %d) created, will sleep for %d\n", ix,
             getpid(), rand_time);
    } else if (pid > 0) {
      printf("Parent: Created Child Process %d (PID: %d)\n", ix, getpid());
      // printf("Parent: Child Process %d (PID: %d) exited\n", ix, getpid());
    } else {
      perror("Fork Failed\n");
    }
  }
}
