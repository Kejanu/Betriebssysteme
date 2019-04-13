
//
// Created by Alex on 13.04.2019.
//
#include <stdio.h>
#include <stdlib.h>

//Zahlenprüfung bis 10

void qZahlen(int grenze){


    for(int i=5; i<=grenze; i++){ //erste solche Zahl
        int done=0; //Falls Treffer -> Abbruch
        for(int a=1; done==0 && a<=10; a++){ //Zahl1
            for(int b=1;done==0 && b<=10; b++){ //Zahl2
                if( a!=b && a*a + b*b == i){ //Schließt gleiche Zahlen aus
                    printf("%d: %d + %d\n", i, a, b);
                    done=1;

                }
            }
        }
    }
}


int main(int argc, char *argv[]){

    if(argc<2){
        printf("Fehler: Keine Obergrenze angegeben\n");
    }else if(argc>2){
        printf("Fehler: Zu viele Parameter\n");
    }else{
        char *p;
        int value= strtol(argv[1], &p , 10);
        if(value==0 && p!=0){
            printf("Fehler: Text angegeben\n");
        }else
        if(value<0){
            printf("Fehler: Negative Zahl als Obergrenze angegeben\n");
        }else if(value%1 !=0){
            printf("Fehler: Keine ganze Zahl\n");
        }else{
            qZahlen(value);
        }
    }


    return 0;
}
