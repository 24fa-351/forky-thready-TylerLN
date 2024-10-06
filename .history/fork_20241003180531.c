#include <stdio.h>
#include <stdlib.h>

#include "process.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
    return 1;
  }

  int num_things = atoi(argv[1]);

  if (num_things < 1 || num_things > 256) {
    fprintf(stderr, "Number of processes must be between 1 and 256.\n");
    return 1;
  }

  create_processes(num_processes);  // Start process creation

  return 0;
}
