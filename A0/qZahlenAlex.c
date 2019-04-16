//
// Created by Alex on 13.04.2019.
//
#include <stdio.h>



void qZahlen(void){


    for(int i=5; i<=100; i++){ //erste solche Zahl

        int done=0; //Falls ein Treffer vorliegt -> Abbruch

        for(int a=1; done==0 && a<=10; a++){
            for(int b=1;done==0 && b<=10; b++){

                if( a!=b && a*a + b*b == i){ //schließt Kombination gleicher Zahlen aus
                    printf("%d: %d^2 + %d^2\n", i, a, b);
                    done=1;

                }
            }
        }
    }
}


int main(void){
    qZahlen();
    return 0;
}
