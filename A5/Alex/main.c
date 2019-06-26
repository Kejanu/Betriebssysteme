#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "a5.h"

int main(int argc, char *argv[])
{
    long int bufferSize = 512;
    long int mode = 0;
    if (argc < 4 || argc > 5) {
        printf("Fehler: Falsche Anzahl an Parametern!\n");
        printf("Nutzung: %s <modus> <quelle> <ziel> [puffergroesse]\n",argv[0]);
        return -1;
    }
    
    errno = 0;
    mode = strtol(argv[1],NULL,10);
    if (errno != 0) {
        printf("Fehler: Modus konnte nicht gelesen werden!\n");
        return -2;
    }
    if (mode < 1 || mode > 4) {
        printf("Fehler: Modus ist ungueltig!\n");
        return -4;
    }
    if (argc == 5) {
        errno = 0;
        bufferSize = strtol(argv[4],NULL,10);
        if (errno != 0) {
            printf("Fehler: Puffergroesse konnte nicht gelesen werden!\n");
            return -8;
        }
        if (bufferSize <= 0) {
            printf("Fehler: Puffergroesse muss groeßer 0 sein!\n");
            return -16;
        }
    }
    switch(mode) {
        case 1:
            copyUsingBuffer(argv[2], argv[3], bufferSize);
            return 0;
        case 2:
            copyUsingFullRead(argv[2], argv[3]);
            return 0;
        case 3:
            copyUsingMap(argv[2], argv[3]);
            return 0;
        case 4:
            copyUsingSystemCall(argv[2], argv[3]);
            return 0;
        default:
            printf("Dieser Fall duerfte NIEMALS eintreten!");
            return -4;
    }
}
