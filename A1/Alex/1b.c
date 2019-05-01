//
// Created by akala on 29.04.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {

    int auswahl = 0;
    printf("Bitte ein Zahl zur Auswahl eingeben.\n1.ps\n2.ls\n3.date\n");


    if (scanf("%d", &auswahl) != 1) {
        printf("Fehler bei scanf!");
        return 1;
    }


    pid_t returnValue;
    returnValue = fork();

    switch (returnValue) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        default:
            printf("Child PID is %d\n", returnValue);
            pid_t r = waitpid(-1, NULL, 0);
            if (r == -1) {
                if (errno != ECHILD) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
            }
            return 0;

        case 0:

            switch (auswahl) {

                case 1:
                    execlp("ps", "ps", NULL);
                    return -1;
                case 2:
                    execlp("ls", "ls", NULL);
                    return -1;
                case 3:
                    execlp("date", "date", NULL);
                    return -1;
                default:
                    printf("Ungültige Eingabe");
                    return -1;
            }
    }
}



















