#include "pattern1.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_one(int num_processes) {
  pid_t child_array[num_processes];
  int sleep_times[num_processes];
  srand(time(NULL));

  for (int sleep_index = 0; sleep_index < num_processes; sleep_index++) {
    sleep_times[sleep_index] = rand() % 8 + 1;
  }

  printf("** Pattern 1: creating %d processes **\n", num_processes);
  fflush(stdout);

  for (int child_index = 0; child_index < num_processes; child_index++) {
    pid_t pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Parent: created Child Process %d (PID: %d)\n", child_index,
             getpid());
      printf("Process %d (PID: %d) will sleep for %d seconds\n", child_index,
             getpid(), sleep_times[child_index]);

      sleep(sleep_times[child_index]);

      printf("Process %d (PID: %d) sleeping\n", child_index, getpid());
      exit(0);
    } else {
      child_array[child_index] = pid;
    }
  }

  for (int ix = 0; ix < num_processes; ix++) {
    waitpid(child_array[ix], NULL, 0);
    printf("Parent: Child Process %d (PID: %d) has exited\n", ix,
           child_array[ix]);
  }

  printf("** Pattern 1: All children have exited **\n");
}
