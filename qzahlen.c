#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

    int upTo = 100;
    int upperBound = (int)sqrt(upTo);

    int i = 1;
    while(i <= 100) {
        for (int j = 1; j <= upperBound; ++j) {
            for (int k = 1; k <= upperBound; ++k) {
                if ((pow(j,2) + pow(k,2)) == i) {
                    printf("%d kann als %d^2 + %d^2 dargestellt werden\n", i, j ,k);
                    goto AFTERFOR;
                }
            }
        }
        AFTERFOR:
        ++i;
    }

    return 0;
}