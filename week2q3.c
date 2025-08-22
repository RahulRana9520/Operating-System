// III. Write a program to read a file and store your details in that file. Your program should also create
// one more file and store your friends details in that file. Once both files are created, print lines
// which are matching in both files.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

int main() {
    FILE *file1, *file2;
    char line1[MAX_LINE], line2[MAX_LINE];

    // Step 1: Write your details into "me.txt"
    file1 = fopen("me.txt", "w");
    if (file1 == NULL) {
        printf("Error opening me.txt\n");
        return 1;
    }
    fprintf(file1, "Name: Rahul\n");
    fprintf(file1, "Age: 21\n");
    fprintf(file1, "City: Dehradun\n");
    fprintf(file1, "Hobby: Coding\n");
    fclose(file1);

    // Step 2: Write friend's details into "friend.txt"
    file2 = fopen("friend.txt", "w");
    if (file2 == NULL) {
        printf("Error opening friend.txt\n");
        return 1;
    }
    fprintf(file2, "Name: Aman\n");
    fprintf(file2, "Age: 21\n");
    fprintf(file2, "City: Dehradun\n");
    fprintf(file2, "Hobby: Cricket\n");
    fclose(file2);

    // Step 3: Open both files for reading
    file1 = fopen("me.txt", "r");
    file2 = fopen("friend.txt", "r");
    if (file1 == NULL || file2 == NULL) {
        printf("Error opening files for reading.\n");
        return 1;
    }

    printf("Matching lines in both files:\n");

    // Step 4: Compare each line of file1 with all lines of file2
    while (fgets(line1, MAX_LINE, file1) != NULL) {
        rewind(file2);  // Go back to start of file2 for each line1
        while (fgets(line2, MAX_LINE, file2) != NULL) {
            if (strcmp(line1, line2) == 0) {
                printf("%s", line1);  // Matching line
            }
        }
    }

    fclose(file1);
    fclose(file2);

    return 0;
}
