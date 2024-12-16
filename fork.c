#include "pattern.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        perror("Invalid number of arguments.\n");
        return 1;
    }

    int pattern       = atoi(argv[1]);
    int num_processes = atoi(argv[2]);

    if (num_processes < 1 || num_processes > 256) {
        perror("Number of processes is not in range [1, 256]\n");
        return 1;
    }

    fork_processes(num_processes, pattern);

    return 0;
}
