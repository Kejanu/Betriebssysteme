//
// Created by alex on 26.06.19.
//

#include <stdio.h>
#include <stdlib.h>



int main(void){

    char string[500000];

    for (int i = 0; i < 500000 ; ++i) {
        string[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[random() % 26];
    }

    printf(string);
}
