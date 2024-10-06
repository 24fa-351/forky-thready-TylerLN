#include <stdio.h>
#include <stdlib.h>

#include "process.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
    return 1;
  }

  int num_processes = atoi(argv[2]);
  int pattern = atoi(argv[3]);

  if (num_processes < 1 || num_processes > 256) {
    fprintf(stderr, "Number of processes must be between 1 and 256.\n");
    return 1;
  }

  choose_pattern(pattern, num_processes);

  return 0;
}
