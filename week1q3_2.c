#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        exit(1);
    } else if (pid == 0) {
        // Child process sleeps so parent can exit first
        sleep(3);
        printf("Child (PID %d): My parent PID is %d\n", getpid(), getppid());
        exit(0);
    } else {
        // Parent exits before child finishes
        printf("Parent (PID %d): Exiting early.\n", getpid());
        exit(0);
    }

    return 0;
}

// Parent (PID 3001): Exiting early.
// Child (PID 3002): My parent PID is 1
