#include <stdio.h>
#include <stdlib.h>

#include "process.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <number_of_things (1-256)> <pattern (1 or 2)>\n",
           argv[0]);
    return 1;
  }

  int num_things = atoi(argv[1]);
  int pattern = atoi(argv[2]);

  if (num_things < 1 || num_things > 256) {
    printf("Error: number_of_things must be between 1 and 256.\n");
    return 1;
  }

  create_processes(pattern, num_things);

  return 0;
}
