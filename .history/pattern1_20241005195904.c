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

  printf("** Pattern 1: creating %d processes.\n",
         num_processes);  // Inform how many processes are being created.

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();

    if (pid < 0) {
      perror("Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      // Child process
      int sleep_time =
          rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
      printf("Process %d (pid %d) created: will sleep for %d seconds\n", ix,
             getpid(), sleep_time);
      sleep(sleep_time);
      exit(sleep_time);  // Child process exits and passes sleep time as exit
                         // status
    } else {
      // Parent process
      printf("Parent: created child %d (pid %d)\n", ix, pid);
    }
  }

  printf("** Pattern 1: All processes created\n");

  // Parent waits for each child to exit
  for (int iy = 0; iy < num_processes; iy++) {
    int status;
    pid_t exited_pid = wait(&status);  // Wait for any child to exit
    int sleep_time =
        WEXITSTATUS(status);  // Get the sleep time from child's exit status
    printf("Child process with pid %d slept for %d seconds and has exited\n",
           exited_pid, sleep_time);
  }

  printf("** Pattern 1: All children have exited\n");
}
