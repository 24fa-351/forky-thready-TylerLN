#include <stdio.h>
#include <stdlib.h>

#include "pattern1.h"
#include "pattern2.h"

void createprocess(int pattern, int num_processes) {
  if (pattern == 1) {
    fork_pattern_one(num_processes);
  } else if (pattern == 2) {
    fork_pattern_two(num_processes);
  } else {
    perror("Invalid pattern number\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    perror("Invalid number of arguments.\n");
    return 1;
  }

  int pattern = atoi(argv[1]);
  int num_processes = atoi(argv[2]);

  if (num_processes < 1 || num_processes > 256) {
    perror("Number is not in range [1, 256]\n");
    return 1;
  }

  createprocess(pattern, num_processes);

  return 0;
}
