#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void create_process(int num_processes) {
  pid_t pid;
  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();
    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      printf("Process %d beginning. (PID: %d)\n", ix + 1, getpid());
      exit(0);
    } else {
      wait(NULL);
      printf("Process %d finished.\n", ix + 1);
    }
  }
}