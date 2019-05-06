#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    printf("Please choose one Entry:\n1.ps\n2.date\n3.ls\n");

    int choice, failed;
    char* answer[5];
    do {
        failed = 0;
        printf("Your choice (Number): ");

        // Scanf returns number of input items successfully matched and assigned
        if (scanf("%d", &choice) != 1 || choice <= 0 || choice > 3)
            failed = 1;

        if (failed) {
            while (getchar() != '\n');
        }
        else {
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
            if (!failed) {
                printf("Your choice was: %s\n", *answer);
            }
        }
    } while (failed);

    pid_t retval;

    retval = fork();
    switch (retval) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            execlp(*answer, *answer, (char *)NULL);
            break;
        default:
            printf("I'm the parent, my child's pid is: %d\n", retval);
            pid_t waitedFor;

            while ((waitedFor = wait(NULL)) > 0) {
                printf("Child with PID: %d terminated\n", waitedFor);
            }
            if (waitedFor == -1) {
                if (errno != ECHILD) {
                    perror("wait");
                    exit(EXIT_FAILURE);
                }
            }
    }
}
