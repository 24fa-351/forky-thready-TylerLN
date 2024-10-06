#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void create_process(int num_processes) {
  pid_t pid;
  int status;
  int i;
  for (i = 0; i < num_processes; i++) {
    pid = fork();
    if (pid < 0) {
      fprintf(stderr, "Fork failed.\n");
      exit(1);
    } else if (pid == 0) {
      // Child process
      printf("Process %d (PID %d) beginning\n", i, getpid());
      sleep(1);
      exit(0);
    }
    waitpid(pid, &status, 0);
    printf("Process %d (PID %d) finished\n", i, pid);
  }
}