#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// --- Задача 7.9 (д) ---
// Знайти суму мінімального серед елементів з парними номерами (a2, a4...) 
// та максимального серед елементів з непарними номерами (a1, a3...)
void task_7_9_d() {
    printf("\n--- Задача 7.9 (д) ---\n");
    int n;
    printf("Введіть розмір масиву n: ");
    scanf("%d", &n);

    double *a = (double *)malloc(n * sizeof(double));
    printf("Введіть %d елементів масиву:\n", n);
    for (int i = 0; i < n; i++) scanf("%lf", &a[i]);

    double min_even_pos = DBL_MAX; // Для a2, a4 (індекси 1, 3...)
    double max_odd_pos = -DBL_MAX; // Для a1, a3 (індекси 0, 2...)

    int found_even = 0, found_odd = 0;

    for (int i = 0; i < n; i++) {
        // У мові C індекс i=0 відповідає a1 (непарна позиція)
        if (i % 2 == 0) { // a1, a3, a5...
            if (a[i] > max_odd_pos) max_odd_pos = a[i];
            found_odd = 1;
        } else { // a2, a4, a6...
            if (a[i] < min_even_pos) min_even_pos = a[i];
            found_even = 1;
        }
    }

    if (found_even && found_odd) {
        printf("min(a2, a4...) = %g\n", min_even_pos);
        printf("max(a1, a3...) = %g\n", max_odd_pos);
        printf("Результат (сума): %g\n", min_even_pos + max_odd_pos);
    } else {
        printf("Недостатньо елементів для обчислення обох груп.\n");
    }
    free(a);
}

// --- Задача 7.11 (а) ---
// 1. Обчислення значення поліному Чебишова Tn(x)
double chebyshev_value(int n, double x) {
    if (n == 0) return 1.0;
    if (n == 1) return x;

    double t_prev2 = 1.0; // T_{n-2}
    double t_prev1 = x;   // T_{n-1}
    double t_curr = 0;

    for (int i = 2; i <= n; i++) {
        t_curr = 2 * x * t_prev1 - t_prev2;
        t_prev2 = t_prev1;
        t_prev1 = t_curr;
    }
    return t_prev1;
}

// 2. Виведення коефіцієнтів поліному Чебишова ступеня n
// Формула: T_n(x) = 2x * T_{n-1}(x) - T_{n-2}(x)
void chebyshev_coefficients(int n) {
    if (n < 0 || n >= 256) return;

    // Використовуємо double, бо коефіцієнти ростуть до 2^(n-1)
    double c_prev2[256] = {0};
    double c_prev1[256] = {0};
    double c_curr[256] = {0};

    c_prev2[0] = 1.0; // T0 = 1
    if (n >= 1) c_prev1[1] = 1.0; // T1 = x

    if (n == 0) {
        printf("T0(x) = 1\n");
        return;
    }
    if (n == 1) {
        printf("T1(x) = 1*x^1\n");
        return;
    }

    for (int k = 2; k <= n; k++) {
        for (int i = 0; i <= k; i++) {
            double term1 = (i > 0) ? 2 * c_prev1[i-1] : 0;
            double term2 = c_prev2[i];
            c_curr[i] = term1 - term2;
        }
        // Копіюємо для наступної ітерації
        for (int i = 0; i <= k; i++) {
            c_prev2[i] = c_prev1[i];
            c_prev1[i] = c_curr[i];
        }
    }

    printf("Коефіцієнти T%d(x):\n", n);
    for (int i = n; i >= 0; i--) {
        if (c_prev1[i] != 0) {
            printf("%+.0f*x^%d ", c_prev1[i], i);
        }
    }
    printf("\n");
}

int main() {
    task_7_9_d();

    printf("\n--- Задача 7.11 (а) ---\n");
    int n;
    double x;
    printf("Введіть ступінь n та точку x: ");
    scanf("%d %lf", &n, &x);

    printf("Значення T%d(%g) = %f\n", n, x, chebyshev_value(n, x));
    chebyshev_coefficients(n);

    return 0;
}