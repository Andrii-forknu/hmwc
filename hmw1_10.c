#include <stdio.h>

int main() {
    int x[] = {1, 2, 3, 4, 5};
    double y[] = {3.0, 1.0, 5.0, 4.0, 2.1};

    printf(" x |");
    for(int i = 0; i < 5; i++) {
        printf(" %d  |", x[i]);
    }
    
   
    printf("\n---|----|----|----|----|----|\n");

    
    printf(" y |");
    for(int i = 0; i < 5; i++) {

        printf(" %.1f |", y[i]);
    }
    printf("\n");

    return 0;
}