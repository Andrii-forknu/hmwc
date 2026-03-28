#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

// --- Задача 1: Робота з тризначним числом ---
void task1() {
    printf("\n--- Задача 1: Розряди числа ---\n");
    int n;
    printf("Введіть тризначне число: ");
    scanf("%d", &n);
    n = abs(n); // працюємо з модулем

    int units = n % 10;
    int tens = (n / 10) % 10;
    int hundreds = n / 100;

    printf("а) Одиниць: %d, Десятків: %d, Сотень: %d\n", units, tens, hundreds);
    printf("б) Сума цифр: %d\n", units + tens + hundreds);
    printf("в) Реверс: %d%d%d\n", units, tens, hundreds);
}

// --- Задача 2: Перестановки цифр ---
void task2() {
    printf("\n--- Задача 2: Перестановки ---\n");
    int n;
    printf("Введіть тризначне число: ");
    scanf("%d", &n);
    int a = n / 100, b = (n / 10) % 10, c = n % 10;

    if (a != b && b != c && a != c) {
        printf("Можливі числа: \n");
        int d[] = {a, b, c};
        // Проста генерація 6 перестановок для 3 цифр
        printf("%d%d%d, %d%d%d, %d%d%d, %d%d%d, %d%d%d, %d%d%d\n",
               a,b,c, a,c,b, b,a,c, b,c,a, c,a,b, c,b,a);
    } else {
        printf("Не всі цифри різні.\n");
    }
}

// --- Задача 3: Добуток чисел через кому ---
void task3() {
    printf("\n--- Задача 3: Добуток (через кому) ---\n");
    long long a, b, c;
    printf("Введіть 3 числа через кому (напр. 10,20,30): ");
    scanf("%lld,%lld,%lld", &a, &b, &c);
    
    // Для 2^21 добуток може сягнути ~2^63, тому використовуємо long long
    long long product = a * b * c;
    printf("Добуток: %lld\n", product);
}

// --- Задача 4: 8-бітний добуток ---
uint16_t multiply8bit(uint8_t a, uint8_t b) {
    return (uint16_t)a * b;
}

void task4() {
    printf("\n--- Задача 4: uint8_t * uint8_t ---\n");
    int a, b;
    printf("Введіть два числа (0-255): ");
    scanf("%d %d", &a, &b);
    printf("Результат (16-біт): %u\n", multiply8bit((uint8_t)a, (uint8_t)b));
}

// --- Задача 5: Більше та менше ---
void task5() {
    printf("\n--- Задача 5: Min/Max ---\n");
    double x, y;
    printf("Введіть два числа: ");
    scanf("%lf %lf", &x, &y);
    printf("Більше: %g, Менше: %g\n", (x > y ? x : y), (x < y ? x : y));
}

// --- Задача 6: Max/Min за модулем ---
void task6() {
    printf("\n--- Задача 6: Max/Min за модулем ---\n");
    double a, b, c;
    printf("Введіть три числа: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    double ma = fabs(a), mb = fabs(b), mc = fabs(c);
    double max_mod = ma > mb ? (ma > mc ? ma : mc) : (mb > mc ? mb : mc);
    double min_mod = ma < mb ? (ma < mc ? ma : mc) : (mb < mc ? mb : mc);
    
    printf("Найбільше за модулем: %g\n", max_mod);
    printf("Найменше за модулем: %g\n", min_mod);
}

// --- Задача 7: Рівняння ---
void solve_quadratic(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) printf(c == 0 ? "Безліч розв'язків\n" : "Немає розв'язків\n");
        else printf("x = %g\n", -c / b);
        return;
    }
    double D = b * b - 4 * a * c;
    if (D < 0) printf("Дійсних розв'язків немає\n");
    else if (D == 0) printf("Один корінь: x = %g\n", -b / (2 * a));
    else printf("x1 = %g, x2 = %g\n", (-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a));
}

void solve_biquadratic(double a, double b, double c) {
    printf("Для ax^4 + bx^2 + c = 0:\n");
    // Заміна t = x^2
    double D = b * b - 4 * a * c;
    if (D < 0) { printf("Немає коренів\n"); return; }
    
    double t1 = (-b + sqrt(D)) / (2 * a);
    double t2 = (-b - sqrt(D)) / (2 * a);
    
    int found = 0;
    if (t1 >= 0) { printf("x1,2 = ±%g; ", sqrt(t1)); found = 1; }
    if (t2 >= 0 && t2 != t1) { printf("x3,4 = ±%g", sqrt(t2)); found = 1; }
    if (!found) printf("Дійсних розв'язків немає");
    printf("\n");
}

void task7() {
    printf("\n--- Задача 7: Рівняння ---\n");
    double a, b, c;
    printf("Введіть коефіцієнти a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    printf("Квадратне: "); solve_quadratic(a, b, c);
    solve_biquadratic(a, b, c);
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    return 0;
}