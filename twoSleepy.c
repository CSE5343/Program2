#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
 * Preston Tighe
 * CSE 5343 - Operating Systems
 * Processor Evans
 * The parent process starts in the new state -> ready state -> running state.
 * When fork is called the child process goes from new -> ready state.
 * Both parent and child run about the same time and cycle from running -> blocked -> ready
 * The dispatcher decides the order in which the processes will execute.
 *
 * PART 2:
 * The parent process completes immediately before the child can run.
 * The child process just becomes orphaned and doesn't have the same PPID of the original process.
 * The child process runs immediately after the original process with a PPID of 1.
 * They don't have the same PPID. It looks like the child is a process of its own.
*/

int main(int argc, char *argv[]) {
    int count;
    if (argc == 2) {
        count = atoi(argv[1]);
    } else {
        count = 5;
    }

    int f = fork();

    for (int i = 1; i <= count; i++) {
        sleep(1);
        if (f == 0) {
            printf("Child process with with PID: %i and PPID: %i; tick %i\n", getpid(), getppid(), i);
        } else {
            printf("Original process with with PID: %i and PPID: %i; tick %i\n", getpid(), getppid(), i);
        }
    }

    if (f == 0) {
        printf("Child process terminating\n");
        exit(0);
    } else {
        wait(NULL);
        printf("Parent process terminating\n");
        exit(0);
    }
}