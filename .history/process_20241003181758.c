#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void create_process(int num_processes) {
  pid_t *pids = malloc(num_processes * sizeof(pid_t));
  if (pids == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(1);
  }

  for (int ix = 0; ix < num_processes; ix++) {
    pids[ix] = fork();
    if (pids[ix] < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pids[ix] == 0) {
      printf("Process %d (PID %d) beginning\n", ix + 1, getpid());
      pause();  // Wait for a signal to exit
      printf("Process %d (PID %d) exiting\n", ix + 1, getpid());
      exit(0);
    }
  }

  // Ensure the initial parent waits for all child processes to print
  // "beginning"
  sleep(2);  // Give some time for all children to print "beginning"

  for (int ix = 0; ix < num_processes; ix++) {
    kill(pids[ix], SIGCONT);     // Send signal to continue and exit
    waitpid(pids[ix], NULL, 0);  // Wait for the specific child to exit
  }

  free(pids);
}