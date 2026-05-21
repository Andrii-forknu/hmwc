#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --- ЗАДАЧА 1: Сума квадратів ---
void solve_task1() {
    int n;
    printf("\n--- Задача 1 ---\nВведіть n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return;

    double *arr = (double*)malloc(n * sizeof(double));
    double sum = 0;
    printf("Введіть %d дійсних чисел: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
        sum += arr[i] * arr[i];
    }
    printf("Сума квадратів: %.2lf\n", sum);
    free(arr);
}

// --- ЗАДАЧА 2: Повні квадрати та куби ---
int input_until_zero(int *arr) {
    int count = 0;
    int num;
    printf("Вводьте числа (0 - кінець, макс 100): ");
    while (count < 100) {
        scanf("%d", &num);
        if (num == 0) break;
        arr[count++] = num;
    }
    return count;
}

void solve_task2() {
    int array[100];
    printf("\n--- Задача 2 ---\n");
    int size = input_until_zero(array);
    int sq = 0, cb = 0;

    for (int i = 0; i < size; i++) {
        int r_sq = (int)round(sqrt(array[i]));
        int r_cb = (int)round(cbrt(array[i]));
        if (array[i] >= 0 && r_sq * r_sq == array[i]) sq++;
        if (r_cb * r_cb * r_cb == array[i]) cb++;
    }
    printf("Знайдено: повних квадратів - %d, повних кубів - %d\n", sq, cb);
}

// --- ЗАДАЧА 3: Динамічні вектори ---
double* create_vector(int n) {
    double *v = (double*)malloc(n * sizeof(double));
    if (!v) return NULL;
    printf("Елементи вектора (%d): ", n);
    for (int i = 0; i < n; i++) scanf("%lf", &v[i]);
    return v;
}

void solve_task3() {
    int n1, n2;
    printf("\n--- Задача 3 ---\nРозмір 1-го вектора: "); scanf("%d", &n1);
    double *v1 = create_vector(n1);
    printf("Розмір 2-го вектора: "); scanf("%d", &n2);
    double *v2 = create_vector(n2);

    if (n1 == n2) {
        printf("Різниця: ");
        double *res = (double*)malloc(n1 * sizeof(double));
        for (int i = 0; i < n1; i++) {
            res[i] = v1[i] - v2[i];
            printf("%.2lf ", res[i]);
        }
        printf("\n");
        free(res);
    } else {
        printf("Помилка: Розмірності не збігаються.\n");
    }
    free(v1); free(v2);
}

// --- ЗАДАЧА 4: Матриці (Лінійний масив) ---
double* create_mat_lin(int n) {
    double *m = (double*)calloc(n * n, sizeof(double));
    printf("Елементи матриці %dx%d:\n", n, n);
    for (int i = 0; i < n * n; i++) scanf("%lf", &m[i]);
    return m;
}

void solve_task4() {
    int n;
    printf("\n--- Задача 4 (Лінійна матриця) ---\nРозмір n: ");
    scanf("%d", &n);
    double *a = create_mat_lin(n);
    double *b = create_mat_lin(n);
    double *c = (double*)calloc(n * n, sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i * n + j] += a[i * n + k] * b[k * n + j];

    printf("Результат множення:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%.2lf ", c[i * n + j]);
        printf("\n");
    }
    free(a); free(b); free(c);
}

// --- ГОЛОВНЕ МЕНЮ ---
int main() {
    int choice;
    while (1) {
        printf("\n--- МЕНЮ ---\n1. Сума квадратів\n2. Квадрати/куби\n3. Різниця векторів\n4. Множення матриць\n0. Вихід\nВибір: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;

        switch (choice) {
            case 1: solve_task1(); break;
            case 2: solve_task2(); break;
            case 3: solve_task3(); break;
            case 4: solve_task4(); break;
            default: printf("Невірний вибір.\n");
        }
    }
    return 0;
}