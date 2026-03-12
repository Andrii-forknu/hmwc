#include <stdio.h>
#include <math.h>

/**
 * Задача 5.16д: Наближене обчислення суми ряду для e^x.
 * Сума рахується доти, доки абсолютна величина доданка >= eps.
 */
double calculate_exp(double x, double eps) {
    double sum = 1.0;  // Перший член ряду (x^0 / 0!)
    double term = 1.0; // Поточний доданок
    int i = 1;

    while (fabs(term) >= eps) {
        term *= x / i; // Рекурентне обчислення наступного члена: term_i = term_{i-1} * (x / i)
        sum += term;
        i++;
    }

    return sum;
}

/**
 * Задача 5.9а: Обчислення n-го елемента рекурентної послідовності.
 * v0 = 1, v1 = 0.3, vi = (i + 2) * v_{i-2}
 */
double calculate_sequence_element(int n) {
    if (n == 0) return 1.0;
    if (n == 1) return 0.3;

    double v_prev2 = 1.0; // v_{i-2}
    double v_prev1 = 0.3; // v_{i-1}
    double v_curr = 0;

    for (int i = 2; i <= n; i++) {
        v_curr = (i + 2) * v_prev2;
        
        // Оновлюємо значення для наступного кроку
        v_prev2 = v_prev1;
        v_prev1 = v_curr;
    }

    return v_curr;
}

int main() {
    // Тестування задачі 16д
    double x, eps;
    printf("--- Задача 5.16д (e^x) ---\n");
    printf("Введіть x та точність eps: ");
    if (scanf("%lf %lf", &x, &eps) == 2) {
        double result = calculate_exp(x, eps);
        printf("Обчислене e^%g = %.10f\n", x, result);
        printf("Константа exp(%g) = %.10f\n\n", x, exp(x));
    }

    // Тестування задачі 9а
    int n;
    printf("--- Задача 5.9а (Послідовність) ---\n");
    printf("Введіть номер елемента n: ");
    if (scanf("%d", &n) == 1) {
        if (n < 0) {
            printf("Номер має бути невід'ємним.\n");
        } else {
            double vn = calculate_sequence_element(n);
            printf("v[%d] = %g\n", n, vn);
        }
    }

    return 0;
}