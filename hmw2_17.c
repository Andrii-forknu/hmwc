#include <stdio.h>
#include <math.h>
double arctg(double x) {
    return atan(x);
}

double arctg_derivative(double x) {
    return 1.0 / (1.0 + pow(x, 2));
}

int main() {
    double x;
    printf("Введіть значення x: ");
    scanf("%lf", &x);

    printf("f(x)  = arctg(%.2f) = %.4f\n", x, arctg(x));
    printf("f'(x) = derivative  = %.4f\n", arctg_derivative(x));

    return 0;
}