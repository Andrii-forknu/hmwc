#include <stdio.h>
#include <math.h>
//comment
double function_15_a(double x, double y) {
    return pow(x, 3) + 3 * pow(x, 2) * y + 3 * x * pow(y, 2) + pow(y, 3);
}


double function_15_b(double x, double y) {
    double xy = x * y;
    return pow(xy, 2) + pow(xy, 3) + pow(xy, 4);
}

int main() {
    double x, y;

    printf("Введіть числа x та y через пробіл:");
    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("Помилка введення!\n");
        return 1;
    }

    printf("Результат 15 (а): %.4f\n", function_15_a(x, y));
    printf("Результат 15 (б): %.4f\n", function_15_b(x, y));

    return 0;
}