#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("Please choose one Entry:\n1.ps\n2.date\n3.ls\n");

    int choice;
    printf("Your choice (Number): ");
    if (scanf("%d", &choice) < 1) {
        printf("Error while executing scanf\n");
        return 1;
    }

    // size 5, cause text + terminating 0
    char* answer[5];


    switch (choice) {
        case 1:
            *answer = "ps";
            break;
        case 2:
            *answer = "date";
            break;
        case 3:
            *answer = "ls";
            break;
        default:
            printf("Your choice wasn't in the specified range. Program exiting...\n");
            return 1;
    }

    printf("Your choice was: %s\n", *answer);
}