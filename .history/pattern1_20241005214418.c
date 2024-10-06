void fork_pattern_two(int num_processes) {
  pid_t pid;
  srand(time(NULL));

  // The main parent process
  printf("** Pattern 2: creating %d processes **\n", num_processes);

  for (int ix = 0; ix < num_processes; ix++) {
    pid = fork();  // Fork a new process

    if (pid < 0) {
      perror("Fork Failed");
      exit(1);
    } else if (pid == 0) {
      // This is the child process
      printf("Child %d (pid %d): starting\n", ix, getpid());

      // If it's not the last child, create the next child
      if (ix < num_processes - 1) {
        printf(
            "Child %d (pid %d), sleeping 9 seconds after creating child %d "
            "(pid %d)\n",
            ix, getpid(), ix + 1, getpid());
        sleep(9);      // Simulate some work before creating the next child
        pid = fork();  // Create the next child
        if (pid < 0) {
          perror("Fork Failed");
          exit(1);
        }
        // Only the current child process should execute this
        if (pid == 0) {
          // New child process created
          printf("Child %d (pid %d): starting\n", ix + 1, getpid());
          printf("Child %d (pid %d) [no children created] sleeping 9 seconds\n",
                 ix + 1, getpid());
          sleep(9);  // Simulate work
          printf("Child %d (pid %d) exiting.\n", ix + 1, getpid());
          exit(0);
        }
      } else {
        printf("Child %d (pid %d) [no children created] sleeping 9 seconds\n",
               ix, getpid());
        sleep(9);  // Simulate work
      }

      // Wait for the next child process to exit if it was created
      if (ix < num_processes - 1) {
        wait(NULL);
        printf("Child %d (pid %d) exiting.\n", ix, getpid());
        exit(0);  // Exit after the next child exits
      }
    } else {
      // This is the parent process
      printf("Parent: created child %d (pid %d)\n", ix, pid);
      if (ix == 0) {
        wait(NULL);  // Wait for the first child to exit
        printf("Parent: child %d (pid %d) has exited\n", ix, pid);
      }
    }
  }

  // Wait for all child processes to finish
  for (int ix = 0; ix < num_processes; ix++) {
    wait(NULL);
  }

  printf("** Pattern 2: All children have exited **\n");
}
