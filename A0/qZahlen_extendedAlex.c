
//
// Created by Alex on 13.04.2019.
//
#include <stdio.h>
#include <stdlib.h>

//Zahlenprüfung bis 10

void qZahlen(int grenze){

    //int zahlen=5;
    for(int i=5; i<=grenze; i++){ //erste solche Zahl
        int done=0;
        for(int a=1; done==0 && a<=10; a++){
            for(int b=1;done==0 && b<=10; b++){
                if( a!=b && a*a + b*b == i){
                    printf("%d: %d^2 + %d^2\n", i, a, b);
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
        int value= strtol(argv[1],NULL , 10);
        if(value<0){
            printf("Fehler: Negative Zahl als Obergrenze angegeben\n");
        }else{
            qZahlen(value);
        }
    }


    return 0;
}
