


#include <stdio.h>

int main(void){

    //Abfrage des gewünschten Aufrufs

    int auswahl=0;
    printf("Bitte ein Zahl zur Auswahl eingeben.\n1.ps\n2.ls\n3.date\n");


    if(scanf("%d", &auswahl) != 1){
        printf("Fehler bei scanf!");
        return 1;
    }

    //Ausgabe

    switch(auswahl){

        case 1: printf("ps"); return 0;
        case 2: printf("ls"); return 0;
        case 3: printf("date"); return 0;
        default: printf("Ungültige Eingabe"); return 1;



    }




}

