// II. Write a program to print process Id's of parent and child process i.e. parent should print its own
// and its child process id while child process should print its own and its parent process id. (use
// getpid(), getppid())

// Use getpid() to print current process ID
// Use getppid() to print parent process ID

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    } else if (pid == 0) {
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else {
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }
    return 0;
}


// Parent Process:
// Parent PID: 5023
// Child PID: 5024

// Child Process:
// Child PID: 5024
// Parent PID: 5023
