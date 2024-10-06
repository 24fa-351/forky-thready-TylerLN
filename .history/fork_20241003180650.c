#include <stdio.h>
#include <stdlib.h>

#include "process.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
    return 1;
  }

  int num_processes = atoi(argv[1]);

  if (num_processes < 1 || num_processes > 256) {
    fprintf(stderr, "Number of processes must be between 1 and 256.\n");
    return 1;
  }

  create_process(num_processes);  // Start process creation

  return 0;
}
