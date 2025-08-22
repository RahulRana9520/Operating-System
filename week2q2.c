// II. Write a program to show working of execlp() system call by executing ls command.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Before executing ls command...\n");

    // Replace current process with 'ls' command using execlp
    execlp("ls", "ls", "-l", NULL);

    // If execlp fails, this line will run
    printf("execlp failed to execute ls command.\n");

    return 0;
}
