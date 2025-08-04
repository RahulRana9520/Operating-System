// I. Write a program to open a directory and list its contents. (use opendir(), readdir(), closedir() )
// Open a directory using opendir()
// Read its contents using readdir()
// Close it using closedir()

#include <stdio.h>
#include <dirent.h> 

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");

    if (dir == NULL) {
        printf("Unable to open directory.\n");
        return 1;
    }

    printf("Contents of the current directory:\n");

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}
