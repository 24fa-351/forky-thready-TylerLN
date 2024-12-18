#include "pattern.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void child_process(int jx, int num_processes, int *sleep_times,
                   int pattern_type) {
    printf("Process %d (PID: %d): starting\n", jx, getpid());

    if (pattern_type == 2 && jx < num_processes - 1) {
        printf("Process %d (PID: %d) creating child %d\n", jx, getpid(),
               jx + 1);
    }

    printf("Process %d (PID: %d), sleeping for %d seconds\n", jx, getpid(),
           sleep_times[jx]);
    sleep(sleep_times[jx]);

    printf("Process %d (PID: %d) has finished sleeping\n", jx, getpid());
    exit(0);
}

void parent_process(int num_processes, pid_t *child_array) {
    for (int ix = 0; ix < num_processes; ix++) {
        waitpid(child_array[ix], NULL, 0);
        printf("Parent: Child %d (PID: %d) has exited\n", ix, child_array[ix]);
    }
    printf("** All children have exited **\n");
}

void fork_processes(int num_processes, int pattern_type) {
    pid_t child_array[num_processes];
    int sleep_times[num_processes];
    srand(time(NULL));

    for (int iy = 0; iy < num_processes; iy++)
        sleep_times[iy] = rand() % 8 + 1;

    printf("** Creating %d processes (Pattern %d) **\n", num_processes,
           pattern_type);
    fflush(stdout);

    if (pattern_type == 1) {
        for (int iz = 0; iz < num_processes; iz++) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("Fork Failed");
                exit(1);
            } else if (pid == 0) {
                printf("Process %d (PID: %d), will sleep for %d seconds\n", iz,
                       getpid(), sleep_times[iz]);
                child_process(iz, num_processes, sleep_times, pattern_type);
            } else {
                child_array[iz] = pid;
            }
        }

        parent_process(num_processes, child_array);

    } else if (pattern_type == 2) {
        for (int iz = 0; iz < num_processes; iz++) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("Fork Failed");
                exit(1);
            } else if (pid == 0) {
                if (iz == 0)
                    printf("Main created Process 0 (PID: %d)\n", getpid());
                printf("Process %d (PID: %d), will sleep for %d seconds after "
                       "creating process %d\n",
                       iz, getpid(), sleep_times[iz], iz + 1);

                child_process(iz, num_processes, sleep_times, pattern_type);
            } else {
                child_array[iz] = pid;

                if (pattern_type == 2 && iz == 0)
                    printf("Parent created Process 0 (PID: %d)\n", pid);
            }
        }

        parent_process(num_processes, child_array);
    }
}