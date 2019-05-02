//
// Created by Long on 01.05.2019.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int exitcode = 0;
    int eingabeZahl;
    label: printf("Bitte eingeben: \n"
                  "[1] ps\n"
                  "[2] date\n"
                  "[3] ls\n"
                  "[4] exit\n");

    scanf("%d",  &eingabeZahl);

    char eingabe[5];

    if(eingabeZahl== 1){
        strcpy(eingabe, "ps");
    }
    else if(eingabeZahl == 2){
        strcpy(eingabe, "date");
    }
    else if(eingabeZahl == 3) {
        strcpy(eingabe, "ls");
    }
    else if(eingabeZahl == 4) {
        printf("Program is now exiting.\n");
        exitcode = 0;
        goto end;
    }
    else{
        printf("Sie haben kein valides Argument angegeben.\n");
        goto label;
    }
    //implicit flushing by adding a \n
    printf("Sie haben %d eingegeben und damit Option %s. \n",     eingabeZahl,eingabe);


    int pid = fork();
    if(pid < 0){
        printf("Fork ist fehlgeschlagen.");
    }
    else if(pid == 0){
        int pidChild = getpid();
        printf("Kindprozess. Die ID ist %d.\n", pidChild);
        execlp(eingabe, eingabe, (char *)NULL);
        return 0;
    }
    else{
        int pidParent = getpid();
        printf("Elternprozess. Die ID ist %d .\n", pidParent);
        wait(NULL);
        goto label;

    }
    end: return exitcode;
}


