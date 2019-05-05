
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(void) {
/*

    while (1) {

        char auswahl[5];
        printf("\nBitte ein Zahl zur Auswahl eingeben.\n1.ps\n2.ls\n3.date\n");


        /*if (scanf("%100s", &auswahl) != 1) {
            printf("Fehler bei scanf!");
            return 1;
        }

        *//*
         * Der Zeiger ptr, welcher den Rückgabewert abfängt, zeigt auf das erste Zeichen des jeweiligen Abschnittes
         * in string. Das jeweilige Ende wird mit \0 in string gesetzt. D.h. der String wird verändert.
         * Deshalb sollte man beim Verwenden von strtok immer nur eine Kopie eines Strings übergeben.
         *//*
        char* secondHalf = &auswahl[4];

        if (strncmp("exit", auswahl, 4)==0 &&
        //funtioniert nicht  array mit leerzeichen
        strncmp("", secondHalf, 96 )==0) {
            printf("Programm beendet\n");
            return 0;
        }


        if (scanf("%4s", &auswahl) != 1) {
            printf("Fehler bei scanf!");
            return 1;
        }

        if (strncmp("exit", auswahl, 4)==0) {
            printf("Programm beendet\n");
            return 0;
        }

        int zahl=0;

        char* pointer;

        pointer = strtok(auswahl, " ");

        if(pointer!=NULL){

            if(strncmp(pointer, "ls", 2)==0){
                zahl=2;
                // neuer string ab [3] einfügen
            }
            if(strncmp(pointer, "ps", 2)==0){
                zahl=1;
            }
            if(strncmp(pointer, "date", 4)==0){
                zahl=3;
            }
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
                break;

            case 0:



                switch (zahl) {

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
                        printf("Ungültige Eingabe\n");
                        return -1;
                }

        }
    }
    */

    while (1) {

        char auswahl[5];
        printf("\nBitte ein Zahl zur Auswahl eingeben.\n1.ps\n2.ls\n3.date\n");


        if (scanf("%4s", &auswahl) != 1) {
            printf("Fehler bei scanf!");
            return 1;
        }

        if (strncmp("exit", auswahl, 4)==0) {
            printf("Programm beendet\n");
            return 0;
        }

        int zahl = strtol(&auswahl[0], NULL , 10 );

        char argumente[101];

        printf("Bitte Argumente angeben.");

        if (scanf("%100s", &argumente) > 1) {
            printf("Fehler bei scanf!");
            return 1;
        }

        if (strncmp("exit", argumente, 4)==0) {
            printf("Programm beendet\n");
            return 0;
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
                break;

            case 0:



                switch (zahl) {

                    case 1:
                        execvp("ps", &argumente);
                        return -1;
                    case 2:
                        execvp("ls", &argumente);
                        return -1;
                    case 3:
                        execvp("date", &argumente);
                        return -1;
                    default:
                        printf("Ungültige Eingabe\n");
                        return -1;
                }

        }
    }

}





















