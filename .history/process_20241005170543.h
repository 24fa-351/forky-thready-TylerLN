#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

void fork_pattern_one(int num_processes);
void fork_pattern_two(int num_processes);
void choose_pattern(int pattern, int num_processes);
int rand_time();
pid_t create_child_process(int ix);

#endif  // PROCESS_H
