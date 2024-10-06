#include "pattern2.h"  // Ensure this header has the function prototype

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fork_pattern_two(int num_processes) {
  pid_t pid;
  pid_t pids[num_processes];       // Array to store child process IDs
  int sleep_times[num_processes];  // Array to store sleep times
  srand(time(NULL));

  printf("** Pattern 2: Creating %d processes **\n", num_processes);
  fflush(stdout);

  for (int ix = 0; ix < num_processes; ix++) {
    sleep_times[ix] =
        rand() % 8 + 1;  // Random sleep time between 1 and 8 seconds
    pid = fork();

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      printf("Child %d (pid %d): starting\n", ix, getpid());
      if (ix < num_processes - 1) {
        printf(
            "Child %d (pid %d), sleeping %d seconds after creating child %d\n",
            ix, getpid(), sleep_times[ix], ix + 1);
        sleep(sleep_times[ix]);  // Simulate some work before creating the next
                                 // child
      } else {
        printf("Child %d (pid %d) [no children created] sleeping %d seconds\n",
               ix, getpid(), sleep_times[ix]);
        sleep(sleep_times[ix]);  // Sleep for the last child
      }
      exit(0);  // Exit the child process
    } else {
      // This is the parent process
      pids[ix] = pid;  // Store the child PID
      printf("Parent: created child %d (pid %d)\n", ix, pid);
    }
  }

  // Parent waits for all child processes to finish
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
    printf("Parent: child %d (pid %d) has exited\n", ix, pids[ix]);
  }

  printf("** Pattern 2: All children have exited **\n");
}