#include "pattern2.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_two(int num_processes) {
  pid_t pid;
  int sleep_times[num_processes];  // Store sleep times for each child
  srand(time(NULL));               // Seed random number generator

  printf("** Pattern 2: Creating %d processes **\n", num_processes);
  fflush(stdout);

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();        // Create a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {  // Child process
      printf("Child %d (pid %d): starting\n", ix, getpid());
      if (ix < num_processes - 1) {
        printf(
            "Child %d (pid %d), sleeping %d seconds after creating child %d\n",
            ix, getpid(), sleep_times[ix], ix + 1);
      } else {
        printf("Child %d (pid %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
      }
      sleep(sleep_times[ix]);  // Sleep for the specified time
      exit(0);                 // Exit the child process
    } else {                   // Parent process
      printf("Parent: created child %d (pid %d)\n", ix, pid);
      waitpid(pid, NULL, 0);  // Wait for this specific child to finish
    }
  }

  printf("** Pattern 2: All children have exited **\n");
}
