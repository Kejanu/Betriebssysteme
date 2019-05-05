#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("Please choose one Entry:\n1.ps\n2.date\n3.ls\n");

    int choice, failed;
    do {
        failed = 0;
        printf("Your choice (Number): ");

        // Scanf returns number of input items successfully matched and assigned
        if (scanf("%1d", &choice) != 1 || choice <= 0 || choice > 3)
            failed = 1;

        if (failed) {
            while (getchar() != '\n');
        } else {
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
                    printf("Your choice wasn't in the specified range. Program restarting...\n");
                    failed = 1;
            }
            if (!failed)
                printf("Your choice was: %s", *answer);
        }
    } while (failed);
}