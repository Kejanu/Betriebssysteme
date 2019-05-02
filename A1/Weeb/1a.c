//
// Created by Long on 01.05.2019.
//
#include <stdio.h>
#include <string.h>

int main(void) {
    int eingabeZahl;
    char eingabe[5];

    printf("Bitte eingeben: \n"
           "[1] ps\n"
           "[2] date\n"
           "[3] ls\n");

    scanf("%d",  &eingabeZahl);

    if(eingabeZahl== 1){
        strncpy(eingabe, "ps", 5);
    }
    else if(eingabeZahl == 2){
        strncpy(eingabe, "date", 5);
    }
    else if(eingabeZahl == 3) {
        strncpy(eingabe, "ls", 5);
    }
    else{
        printf("Sie haben %d eingegeben und damit kein valides Argument ", eingabeZahl);
        return 0;
    }

    printf("Sie haben %d eingegeben und damit Option %s. ", eingabeZahl,eingabe);
    return 0;
}

