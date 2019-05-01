//
// Created by Long on 01.05.2019.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int eingabeZahl;


    printf("Bitte eingeben: \n"
           "[1] ps\n"
           "[2] date\n"
           "[3] ls\n");

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
    else{
        printf("Sie haben %d eingegeben und damit kein valides Argument \n", eingabeZahl);
        return 1;
    }
    //implicit fflushing by adding a \n
    //When you write to 'buffered' device, sometimes the system will hold the characters in the buffer until a specific thing happens:
    //1) the buffer is filled
    //2) a NEWLINE \n is added
    //3) an explicit command (flush) is used
    //It all depends on how the compiler I/O is designed.
    //So on some compilers, a printf() or cout command may not work immediately. Therefore, you flush the buffer when you need the output right away.
    printf("Sie haben %d eingegeben und damit Option %s. \n", eingabeZahl,eingabe);



    int pid = fork();
    if(pid < 0){
        printf("Fork ist fehlgeschlagen.");
    }
    else if(pid == 0){
        int pidChild = getpid();
        printf("Kindprozess. Die ID ist %d.\n", pidChild);
        execlp(eingabe, eingabe, (char *)NULL);
    }
    else{
        int pidParent = getpid();
        printf("Elternprozess. Die ID ist %d .\n", pidParent);
        //prevent Zombies
        wait(NULL);

    }
    return 0;
}
