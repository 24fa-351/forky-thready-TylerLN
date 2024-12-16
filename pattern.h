#ifndef PATTERN_H
#define PATTERN_H
#include <sys/types.h>

void fork_processes(int num_processes, int pattern_type);
void child_process(int child_index, int num_processes, int *sleep_times,
                   int pattern_type);
void parent_process(int num_processes, pid_t *child_array);

#endif
