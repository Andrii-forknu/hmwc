#include <stdio.h>
#include <float.h> 

double relu(double x) {
    return (x > 0) ? x : 0.0;
}

double relu_derivative(double x) {
    return (x >= 0) ? 1.0 : 0.0;
}

int main() {
    double x = 0.0;
    
    printf("x = %.1f\n", x);
    printf("ReLU'(x) = %.1f\n", relu_derivative(x));

    return 0;
}