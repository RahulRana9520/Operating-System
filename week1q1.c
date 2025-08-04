// I. Write a program to create a child process using system call fork().

#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    } else if (pid == 0) {
        printf("This is the child process.\n");
    } else {
        printf("This is the parent process.\n");
    }

    return 0;
}


// Output:
// This is the parent process.
// This is the child process.
