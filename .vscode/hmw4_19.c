#include <stdio.h>

int main() {
    int n;
    double p = 1.0;

    printf("Введіть натуральне число n (n > 2): ");
    if (scanf("%d", &n) != 1 || n <= 2) {
        printf("Помилка: n має бути цілим числом більше за 2.\n");
        return 1;
    }


    for (int i = 2; i <= n; i++) {
    
        p *= (1.0 - 1.0 / (i * i));
    }

    printf("Результат добутку p = %.6lf\n", p);

    return 0;
}