#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
void create_processes(int pattern, int num_things) {
  srand(time(NULL));  // Seed the random number generator

  for (int n = 1; n <= num_things; n++) {
    pid_t pid = fork();  // Fork a new process
    if (pid < 0) {
      perror("Fork failed");
      exit(1);
    }

    if (pid == 0) {  // Child process
      // Print the process creation message
      printf("Process %d created (PID: %d)\n", n, getpid());

      // Random sleep time between 1 and 8 seconds
      int sleep_time = rand() % 8 + 1;
      sleep(sleep_time);

      // Print the process beginning message
      printf("Process %d beginning (PID: %d)\n", n, getpid());
      exit(0);  // Child exits after completing its task
    }
  }

  // Ensure the initial parent waits for all child processes to finish
  while (wait(NULL) > 0);
}