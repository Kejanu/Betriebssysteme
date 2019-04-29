//
// Created by akala on 29.04.2019.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /*fuer pid_t benoetigt*/
int main() {
    pid_t retval;
    retval = fork();
    switch (retval) {
        case -1: perror("fork"); exit(EXIT_FAILURE);
        case 0: printf("I'm the child.\n"); break;
        default: printf("I'm the parent, my child's pid is %d.\n",retval);
    }
    return 0;
}