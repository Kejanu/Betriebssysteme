#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Basic input validation
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

    // We use strtol, cause atoi's functionallity wasn't sufficient for us
    inputNumber = strtol(argv[1], &endptr, 10);

    // More input validation
    if (*endptr != '\0') {
        printf("Fehler: Eingabe war Text order keine ganze Zahl");
        return 1;
    }

    if (inputNumber <= 0) {
        printf("Fehler: Eingegebene Zahl ist kleiner als 1");
        return 1;
    }

    printf("Ihre Eingabe: %d\n", inputNumber);

    // Calculate upperBound to ignore redundant loops
    int upperBound = (int)sqrt(inputNumber);

    int i = 1;
    while(i <= inputNumber) {
        for (int j = 1; j <= upperBound; ++j) {
            for (int k = 1; k <= upperBound; ++k) {
                if (j != k && (pow(j,2) + pow(k,2)) == i) {
                    printf("%d kann als %d^2 + %d^2 dargestellt werden\n", i, j ,k);
                    // Use of goto, to only print one result for each iteration of i
                    goto AFTERFOR;
                }
            }
        }
        AFTERFOR:
        ++i;
    }

    return 0;
}