#include <stdio.h>
#include <math.h>

// --- Задача 1: Гармонічне число ---
void task1() {
    printf("\n--- Задача 1: Гармонічне число ---\n");
    double a, sum = 0;
    int n = 0;
    printf("Введіть число a: ");
    scanf("%lf", &a);

    while (sum <= a) {
        n++;
        sum += 1.0 / n;
    }
    printf("а) Перше число > a: %f\n", sum);
    printf("б) Найменше n: %d\n", n);
}

// --- Задача 2: Числа Фібоначчі ---
long long get_fib(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    long long prev = 0, curr = 1, next;
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

void task2() {
    printf("\n--- Задача 2: Фібоначчі ---\n");
    double a;
    printf("Введіть a: ");
    scanf("%lf", &a);

    int n = 0;
    long long f = 0;
    while (get_fib(n + 1) <= a) n++;
    
    printf("а) F(5) = %lld\n", get_fib(5));
    printf("б) Номер найбільшого F <= a: %d (F=%lld)\n", n, get_fib(n));
    printf("в) Номер найменшого F > a: %d (F=%lld)\n", n + 1, get_fib(n + 1));

    long long sum_1000 = 0;
    for (int i = 0; (f = get_fib(i)) <= 1000; i++) sum_1000 += f;
    printf("г) Сума F <= 1000: %lld\n", sum_1000);
}

// --- Задача 3: Гіпотеза Коллатца (3n + 1) ---
void task3() {
    printf("\n--- Задача 3: Сиракузька послідовність ---\n");
    int max_steps = 0, best_n = 1;

    for (int n = 1; n < 1000; n++) {
        long long temp = n;
        int steps = 0;
        while (temp != 1) {
            if (temp % 2 == 0) temp /= 2;
            else temp = 3 * temp + 1;
            steps++;
        }
        if (steps > max_steps) {
            max_steps = steps;
            best_n = n;
        }
    }
    printf("Макс. кількість кроків для n < 1000: %d (n = %d)\n", max_steps, best_n);
}

// --- Задача 4: Добутки ---
void task4() {
    printf("\n--- Задача 4: Добутки ---\n");
    int n;
    printf("Введіть n: ");
    scanf("%d", &n);

    double p1 = 1.0, p2 = 1.0;
    for (int i = 1; i <= n; i++) {
        p1 *= (1.0 + 1.0 / (i * i));
        double term = (i % 2 != 0 ? 1.0 : -1.0) * (i * i) / pow(2, i);
        p2 *= (1.0 + term);
    }
    printf("а) Pn = %f\n", p1);
    printf("б) Pn = %f\n", p2);
}

// --- Задача 5: Рекурентна послідовність ---
void task5() {
    printf("\n--- Задача 5: Пошук додатного члена ---\n");
    double x1 = -99, x2 = -99, x3 = -99, x_curr;
    int n = 4;
    while (1) {
        x_curr = x3 + x1 + 100;
        if (x_curr > 0) break;
        x1 = x2; x2 = x3; x3 = x_curr;
        n++;
    }
    printf("Перший додатний член: x[%d] = %g\n", n, x_curr);
}

// --- Задача 6: Ланцюгові дроби ---
void task6() {
    printf("\n--- Задача 6: Ланцюгові дроби ---\n");
    int n = 5;
    // a) b_n (для b=2)
    double b = 2, res_a = b;
    for (int i = 0; i < n; i++) res_a = b + 1.0 / res_a;
    
    // b) lambda_n
    double res_b = 4.0 * n + 2.0;
    for (int k = 1; k <= n; k++) {
        res_b = 4.0 * (n - k) + 2.0 + 1.0 / res_b;
    }
    
    printf("а) b_n: %f; б) lambda_n: %f\n", res_a, res_b);
}

// --- Задача 7: Сума з рекурентними a_k, b_k ---
void task7() {
    printf("\n--- Задача 7: Сума Sn ---\n");
    int n = 10;
    double a1 = 0, a2 = 1, b1 = 1, b2 = 0;
    double sum = 0;
    
    // Додамо перші два члени
    sum += pow(2, 1) / (a1 + b1) + pow(2, 2) / (a2 + b2);
    
    for (int k = 3; k <= n; k++) {
        double ak = a2 / k + a1;
        double bk = b2 + a2; // у вказівці b_k = b_{k-1} + a_{k-1}
        sum += pow(2, k) / (ak + bk);
        a1 = a2; a2 = ak;
        b1 = b2; b2 = bk;
    }
    printf("S[%d] = %f\n", n, sum);
}

// --- Задача 8: Ряди Тейлора ---
void task8() {
    printf("\n--- Задача 8: Ряди Тейлора ---\n");
    double x, eps;
    printf("Введіть x та точність eps: ");
    scanf("%lf %lf", &x, &eps);

    // a) e^x
    double e_res = 1.0, e_term = 1.0;
    for (int i = 1; fabs(e_term) > eps; i++) {
        e_term *= x / i;
        e_res += e_term;
    }
    
    // б) Інтеграл від e^(-t^2)
    double phi_res = 0, phi_term = x;
    for (int n = 0; fabs(phi_term) > eps; n++) {
        phi_res += phi_term;
        phi_term *= - (x * x * (2 * n + 1)) / ((2 * n + 3) * (n + 1));
    }

    printf("e^x: %f (math.h: %f)\n", e_res, exp(x));
    printf("Phi(x): %f\n", phi_res);
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    return 0;
}