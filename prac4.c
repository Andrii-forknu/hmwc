#include <stdio.h>
#include <math.h>
#include <float.h>

// --- Задача 1: Вкладені синуси ---
double nested_sin(double x, int n) {
    double res = x;
    for (int i = 0; i < n; i++) res = sin(res);
    return res;
}

// --- Задача 2: Рядок факторіала ---
void factorial_string(int n) {
    printf("\nn! зростання: %d! = ", n);
    for (int i = 1; i <= n; i++) printf("%d%s", i, (i == n ? "" : "*"));
    
    printf("\nn! спадання: %d! = ", n);
    for (int i = n; i >= 1; i--) printf("%d%s", i, (i == 1 ? "" : "*"));
    printf("\n");
}

// --- Задача 3 та 4: Многочлени ---
void polynomials() {
    // 3a) n=3, x=2
    int n3 = 3; double x3 = 2, res3a = 0;
    for (int i = 0; i <= n3; i++) res3a += pow(x3, i);
    
    // 3b) n=4, x=1, y=2
    int n4 = 4; double x4 = 1, y4 = 2, res3b = 0;
    for (int i = 0; i <= n4; i++) res3b += pow(x4, 2*i) * pow(y4, i);
    
    // 4) x + 2x^2 + ... + nx^n
    double x_val = 2; int n_val = 3; double res4 = 0;
    for (int i = 1; i <= n_val; i++) res4 += i * pow(x_val, i);

    printf("\n3a) Res: %g; 3b) Res: %g; 4) Res: %g\n", res3a, res3b, res4);
}

// --- Задача 5: Подвійний факторіал ---
long long double_factorial(int n) {
    long long res = 1;
    for (int i = n; i > 0; i -= 2) res *= i;
    return res;
}

// --- Задача 6: Вкладені корені ---
void nested_radicals(int n) {
    // a) sqrt(2 + sqrt(2...))
    double res_a = 0;
    for (int i = 0; i < n; i++) res_a = sqrt(2 + res_a);
    
    // b) sqrt(3 + sqrt(6 + ... + sqrt(3n)))
    double res_b = 0;
    for (int i = n; i >= 1; i--) res_b = sqrt(3 * i + res_b);
    
    printf("\n6a) %f; 6b) %f\n", res_a, res_b);
}

// --- Задача 7: Експонента (ряд) ---
double exp_series(double x, int n) {
    double res = 1.0, term = 1.0;
    for (int i = 1; i <= n; i++) {
        term *= x / i;
        res += term;
    }
    return res;
}

// --- Задача 8 та 9: Степені ---
void powers_tasks(int m, int n) {
    int k = 0;
    while (pow(4, k + 1) <= m) k++;
    printf("\n8) Найбільше k: %d (4^%d <= %d)", k, k, m);

    int r = 0;
    while (pow(2, r) <= n) r++;
    printf("\n9) Найменше 2^r > %d: %g (r=%d)\n", n, pow(2, r), r);
}

// --- Задача 10: Машинний нуль ---
void machine_epsilon() {
    float a = 1.0f;
    while (1.0f + a/2.0f != 1.0f) a /= 2.0f;
    printf("\n10) Машинний нуль (float): %e (Lib: %e)\n", a, FLT_EPSILON);
}

// --- Задача 11: Послідовність ---
void sequence_stats() {
    double val, sum = 0, prod = 1;
    int count = 0;
    printf("\n11) Вводьте числа (0 для виходу):\n");
    while (1) {
        printf("a[%d]=", count);
        scanf("%lf", &val);
        if (val == 0) break;
        sum += val;
        prod *= val;
        count++;
    }
    if (count > 0) {
        printf("Сер. арифм: %g, Сер. геом: %g\n", sum/count, pow(prod, 1.0/count));
    }
}

// --- Задача 12: Субфакторіал ---
long long factorial(int n) {
    long long f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

double subfactorial(int n) {
    double sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += pow(-1, i) / factorial(i);
    }
    return factorial(n) * sum;
}

int main() {
    printf("1) sin(sin(x)) n=5, x=1: %f\n", nested_sin(1.0, 5));
    factorial_string(5);
    polynomials();
    printf("\n5) 5!! = %lld, 6!! = %lld\n", double_factorial(5), double_factorial(6));
    nested_radicals(5);
    printf("\n7) Ряд x=0.5, n=10: %f\n", exp_series(0.5, 10));
    powers_tasks(100, 50);
    machine_epsilon();
    sequence_stats();
    printf("\n12) Субфакторіал !5: %.0f\n", subfactorial(5));
    
    return 0;
}