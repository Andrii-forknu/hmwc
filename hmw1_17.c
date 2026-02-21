#include <stdio.h>


int main() {
    long double x;
    
    printf("Введіть дійсне число (від 0 до 10000): ");
    if (scanf("%Lf", &x) != 1) {
        printf("Помилка введення.\n");
        return 1;
    }

    long double result = x*x*x*x*x*x*x*x; 

    printf("\nРезультат у 8-му степені:\n");
    printf("%25.4Lf\n", result);

    return 0;
}