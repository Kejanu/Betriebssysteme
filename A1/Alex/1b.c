//
// Created by akala on 29.04.2019.
//

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(void){

    int auswahl=0;
    printf("Bitte ein Zahl zur Auswahl eingeben.\n1.ps\n2.ls\n3.date\n");


    if(scanf("%d", &auswahl) != 1){
        printf("Fehler bei scanf!");
        return 1;
    }


    switch(auswahl) {

        case 1:
            printf("ps");
            return 0;
        case 2:
            printf("ls");
            return 0;
        case 3:
            printf("date");
            return 0;
        default:
            printf("Ungültige Eingabe");
            return 1;


    }

            pid_t returnValue;
    returnValue = fork();

    switch (returnValue){
        case -1: perror("fork"); exit(EXIT_FAILURE);
        default: printf("Child PID is %d", returnValue); return 0;
        case 0:
    }



    }

}

