#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

//    printf("Argc: %d\n", argc);
//    printf("Argv: %s\n", argv[0]);

    if (argc <= 1) {
        printf("Fehler: Keine Obergrenze angegeben");
        return 1;
    }

    if (argc >= 3) {
        printf("Fehler: Zu viele Argumente angegeben");
        return 1;
    }

    int inputNumber;
    char *endptr;

    /*
      If endptr is not NULL, strtol() stores the address of the first invalid character in *endptr.
      If there were no digits at all, strtol() stores the original value of nptr in *endptr (and returns 0).
      In particular, if *nptr is not '\0' but **endptr is '\0' on return, the entire string is valid.

      long int strtol(const char *nptr, char **endptr, int base);

     */
    inputNumber = strtol(argv[1], &endptr, 10);

    if (inputNumber <= 0 || strlen(endptr) > 0) {
        printf("Fehler: Eingegebene Zahl ist kleiner als 1 oder keine ganze Zahl");
        return 1;
    }

    printf("Eingabe: %d\n", inputNumber);

    int upTo = inputNumber;
    int upperBound = (int)sqrt(upTo);

    int i = 1;
    while(i <= 100) {
        for (int j = 1; j <= upperBound; ++j) {
            for (int k = 1; k <= upperBound; ++k) {
                if ((pow(j,2) + pow(k,2)) == i) {
                    printf("%d kann als %d + %d dargestellt werden\n", i, j ,k);
                    goto AFTERFOR;
                }
            }
        }
        AFTERFOR:
        ++i;
    }

    return 0;
}