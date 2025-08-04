// III. Write a program to create child process which will list all the files present in your system. Make
// sure that parent process waits until child has not completed its execution. (use wait(), exit())
// What will happen if parent process dies before child process? Illustrate it by creating one more
// child of parent process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        exit(1);
    } else if (pid == 0) {
        // Child process: list files
        printf("Child (PID %d): Listing all files:\n", getpid());
        execlp("ls", "ls", "-l", NULL); // Executes 'ls -l'
        printf("execlp failed\n");
        exit(1);
    } else {
        // Parent process waits for child
        wait(NULL);
        printf("Parent (PID %d): Child has finished execution.\n", getpid());
    }

    return 0;
}
