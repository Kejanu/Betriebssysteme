//
// Created by akala on 13.04.2019.
//
#include <stdio.h>

//Zahlenprüfung bis 10

void qZahlen(void){

    //int zahlen=5;
    for(int i=5; i<=100; i++){ //erste solche Zahl
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


int main(void){
    qZahlen();
    return 0;
}
